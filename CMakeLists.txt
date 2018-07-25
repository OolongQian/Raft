cmake_minimum_required(VERSION 3.10)
project(raft_proj)

set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY(src bin)

INCLUDE_DIRECTORIES(include/)

set(Boost_USE_STATIC_LIBS FALSE)
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread)
add_definitions(
        -D BOOST_THREAD_VERSION=4
        -D BOOST_LOG_DYN_LINK
)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES( include ${Boost_INCLUDE_DIRS} )
#    LINK_LIBRARIES( ${Boost_LIBRARIES} )
ELSE(Boost_FOUND)
    MESSAGE(FATAL_ERROR "Boost package not found")
ENDIF(Boost_FOUND)
