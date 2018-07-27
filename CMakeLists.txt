cmake_minimum_required(VERSION 3.10)
project(raft_proj)

set(CMAKE_CXX_STANDARD 14)
if (MSVC)
    add_definitions(-D _WIN32_WINNT=0x600)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /W4 /Zi /EHsc")
elseif (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o2 -Wall -pthread")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o2 -Wall")
endif ()

#INCLUDE_DIRECTORIES(./include/)

set(Boost_USE_STATIC_LIBS FALSE)
find_package(Boost REQUIRED
        COMPONENTS thread log unit_test_framework serialization)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(
        -D BOOST_THREAD_VERSION=4
        -D BOOST_LOG_DYN_LINK
)

ADD_SUBDIRECTORY(src bin)
