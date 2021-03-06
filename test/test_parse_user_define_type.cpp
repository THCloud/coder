/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   test_parse_user_define_type.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/27 12:56:56
 *
 * @brief  unit test for parse_user_define_type.h
 *
 **/

#include <gtest/gtest.h>
#include "parse_user_define_type.h"
#include "user/user_define_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestParseUserDefineTypeSuite : public ::testing::Test {
public:
    TestParseUserDefineTypeSuite() : _parse_user_type(nullptr) {}
    virtual ~TestParseUserDefineTypeSuite() {}

    virtual void SetUp() {
        _parse_user_type = new goodcoder::ParseUserDefineType
                            <user::UserType>(&user::user_function);
    }

    virtual void TearDown() {
        if (_parse_user_type != nullptr) {
            delete _parse_user_type;
        }
        _parse_user_type = nullptr;
    }

public:
    goodcoder::ParseUserDefineType<user::UserType> *_parse_user_type;
};

TEST_F(TestParseUserDefineTypeSuite, test_parse_user_define_type) {
    user::UserType user_type;
    std::string test_data = "123|1.23|a";
    _parse_user_type->parse_user_define_type(test_data, &user_type);
    ASSERT_EQ(123, user_type.int_val);
    ASSERT_NEAR(1.23, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);

    test_data = "a|a|a";
    _parse_user_type->parse_user_define_type(test_data, &user_type);
    ASSERT_EQ(0, user_type.int_val);
    ASSERT_NEAR(0, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);

    test_data = "||";
    _parse_user_type->parse_user_define_type(test_data, &user_type);
    ASSERT_EQ(0, user_type.int_val);
    ASSERT_NEAR(0, user_type.float_val, 0.001);
}
