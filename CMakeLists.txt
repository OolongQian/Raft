cmake_minimum_required(VERSION 3.10)
project(raft_proj)

set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY(src)

INCLUDE_DIRECTORIES(/include)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES( include ${Boost_INCLUDE_DIRS} )
    LINK_LIBRARIES( ${Boost_LIBRARIES} )
ELSE(Boost_FOUND)
    MESSAGE(FATAL_ERROR "Boost package not found")
ENDIF(Boost_FOUND)
