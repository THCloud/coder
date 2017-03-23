cmake_minimum_required(VERSION 2.8)
project(c_goodcoder)

enable_testing()
option(BUILD_TEST "Build test" ON)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(GFLAGS_INCLUDE_DIR "${GFLAGS_ROOT}/include")
set(GFLAGS_LINK_DIR "${GFLAGS_ROOT}/lib")
# set(GLOG_INCLUDE_DIR "${GLOG_ROOT}/include")
# set(GLOG_LINK_DIR "${GLOG_ROOT}/lib")

include_directories(${GFLAGS_INCLUDE_DIR})
# include_directories(${GLOG_INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

link_directories(${GFLAGS_LINK_DIR})
# link_directories(${GLOG_LINK_DIR})

set(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC -O2 -Wno-parentheses -rdynamic -std=c++11")

set(CPP_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

set(DICT_PARSE_SRC
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)

add_executable(
    dict_parse_demo
    ${CMAKE_SOURCE_DIR}/demo/dict_parse_demo.cpp
    ${CPP_SOURCE_DIR}/user/user_define_type.cpp
    ${DICT_PARSE_SRC}
)
target_link_libraries(
    dict_parse_demo
    gflags
    # glog
)

if(BUILD_TEST)
    add_subdirectory(test)
endif(BUILD_TEST)
