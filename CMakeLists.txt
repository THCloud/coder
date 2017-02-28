cmake_minimum_required(VERSION 2.8)
project(c_goodcoder)

enable_testing()
option(BUILD_TEST "Build test" ON)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

include_directories(${INCLUDE_DIR})

set(CPP_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

set(DICT_PARSE_SRC
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)

add_executable(
    dict_parse_demo
    ${CPP_SOURCE_DIR}/dict_parse_demo.cpp
    ${DICT_PARSE_SRC}
)

if(BUILD_TEST)
    add_subdirectory(test)
endif(BUILD_TEST)
