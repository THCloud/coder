cmake_minimum_required(VERSION 2.8)

enable_testing()

set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")
set(GTEST_LINK_DIR "${GTEST_ROOT}/lib")

include_directories(${GTEST_INCLUDE_DIR})
link_directories(${GTEST_LINK_DIR})

add_executable(
    test_dict_handler
    test_dict_handler.cpp
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)
target_link_libraries(test_dict_handler gtest pthread)

add_executable(
    test_parse_base_type
    test_parse_base_type.cpp
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)
target_link_libraries(test_parse_base_type gtest pthread)

add_executable(
    test_parse_user_define_type
    test_parse_user_define_type.cpp
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)
target_link_libraries(test_parse_user_define_type gtest pthread)

add_executable(
    test_user_function
    test_user_function.cpp
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)
target_link_libraries(test_user_function gtest pthread)

add_executable(
    test_util
    test_util.cpp
    ${CPP_SOURCE_DIR}/dict_handler.cpp
    ${CPP_SOURCE_DIR}/util.cpp
)
target_link_libraries(test_util gtest pthread)
