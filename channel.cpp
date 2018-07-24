#include <atomic>
#include <exception>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

template <class> class Channel; /* undefined */

template <class Ret, class... Args> class Channel<Ret(Args...)> {
private:
  struct Node {
    std::function<Ret(Args...)> f;
    std::atomic<bool> blocked{false};
  };

public:
  Channel() : node(std::make_shared<Node>()) {}
  Channel(const Channel &) = delete;
  Channel(Channel &&) = delete;
  Channel &operator=(const Channel &) = delete;
  Channel &operator=(Channel &&) = delete;
  ~Channel() = default;

  template <class Func> void bind(Func &&f_) {
    node->f = std::forward<Func>(f_);
  }

  void block() { node->blocked = true; }

  void unblock() { node->blocked = false; }

  class Handler {
  public:
    Handler() = default;
    Handler(const Handler &) = default;
    Handler(Handler &&) noexcept = default;
    Handler &operator=(const Handler &) = default;
    Handler &operator=(Handler &&) noexcept = default;
    ~Handler() = default;

    class AssociatedChannelDestroyed : public std::exception {};

    template <class... Ts> decltype(auto) operator()(Ts &&... args) {
      return async(std::forward<Ts>(args)...).get();
    }

    template <class... Ts> decltype(auto) async(Ts &&... args) {
      auto node = node_.lock();
      if (!node)
        throw AssociatedChannelDestroyed();

      auto foo = [this, node](auto &&... args_) {
        while (node->blocked)
          std::this_thread::yield();
        return node->f(std::forward<decltype(args_)>(args_)...);
      };
      return std::async(std::bind(foo, std::forward<Ts>(args)...));
    }

  private:
    friend class Channel;
    explicit Handler(std::shared_ptr<Node> node_) : node_(node_) {}
    std::weak_ptr<Node> node_;
  };

  Handler getHandler() { return Handler(node); }

private:
  std::shared_ptr<Node> node;

}; /* class Channel */

int main() {
  Channel<int(int, int)> c;
  c.bind([](int a, int b) { return a + b; });

  auto add = c.getHandler();
  c.block();

  std::thread t([&add] {
    std::cout << add(1, 2) << std::endl; // output 3 after 3 seconds
  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
  auto fut = add.async(2, 2); // non-blocking
  c.unblock();
  t.join();

  std::cout << fut.get() << std::endl; // output 4

  return 0;
}