cmake_minimum_required(VERSION 2.8)
project(c_goodcoder)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

include_directories(${INCLUDE_DIR})

set(DICT_PARSE_SRC
    ${CMAKE_SOURCE_DIR}/src/dict_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/util.cpp
)

add_executable(
    dict_parse_demo
    ${CMAKE_SOURCE_DIR}/src/dict_parse_demo.cpp
    ${DICT_PARSE_SRC}
)
