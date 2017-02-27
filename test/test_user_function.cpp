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
 * @brief
 *
 **/

#include <gtest/gtest.h>
#include "user_define_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestUserFunctionSuite : public ::testing::Test {
};

TEST_F(TestUserFunctionSuite, test_user_function) {
    goodcoder::UserType user_type;
    std::string test_data = "123|1.23|a";
    goodcoder::user_function(test_data, &user_type);
    ASSERT_EQ(123, user_type.int_val);
    ASSERT_EQ(1.23, user_type.double_val);
    ASSERT_EQ('a', user_type.char_val);
}
