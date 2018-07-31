file(GLOB_RECURSE LIB_SOURCE *.cpp *.cc *.h *.hpp)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE} ${INCLUDE_DIRECTORIES})

# dependecncies
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR};${CMAKE_MODULE_PATH}")

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

# link
find_package(GRPC REQUIRED)
include_directories(${GRPC_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        ${GRPC_LIBRARIES}
        )

ADD_EXECUTABLE(hello ./test/identity/TestFollower.cpp)


target_link_libraries(hello
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        ${GRPC_LIBRARIES})

# some strange problems, add some compile command to fix
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_filesystem")
