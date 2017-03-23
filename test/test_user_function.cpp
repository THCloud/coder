/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   test_user_function.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/27 12:48:17
 *
 * @brief  unit test for user_define_type.h
 *
 **/

#include <gtest/gtest.h>
#include "user/user_define_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestUserFunctionSuite : public ::testing::Test {
};

TEST_F(TestUserFunctionSuite, test_user_function) {
    user::UserType user_type;
    std::string test_data = "123|1.23|a";
    user::user_function(test_data, &user_type);
    ASSERT_EQ(123, user_type.int_val);
    ASSERT_NEAR(1.23, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);
}

TEST_F(TestUserFunctionSuite, test_user_function_with_unexpect_string) {
    std::string test_data = "a|a|a";

    user::UserType user_type;
    goodcoder::ErrorCode ret;
    ret = user::user_function(test_data, &user_type);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(0, user_type.int_val);
    ASSERT_NEAR(0, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);

    test_data = "a|a|a|a|a|a|a";

    ret = user::user_function(test_data, &user_type);
    ASSERT_EQ(goodcoder::TYPE_NOT_MATCH, ret);
}
