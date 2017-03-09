cmake_minimum_required(VERSION 2.8)
project(c_goodcoder)

enable_testing()
option(BUILD_TEST "Build test" ON)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(GFLAGS_INCLUDE_DIR "${GFLAGS_ROOT}/include")
set(GFLAGS_LINK_DIR "${GFLAGS_ROOT}/lib")

include_directories(${GFLAGS_INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

link_directories(${GTEST_LINK_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")


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
target_link_libraries(dict_parse_demo gflags)

if(BUILD_TEST)
    add_subdirectory(test)
endif(BUILD_TEST)
