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
 * @brief
 *
 **/

#include <gtest/gtest.h>
#include "parse_user_define_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS;
}

class TestParseUserDefineTypeSuite : public ::testing::Test {
public:
    TestParseUserDefineTypeSuite() {}
    virtual ~TestParseUserDefineTypeSuite() {}

    virtual void SetUp() {
        _parse_user_type = new goodcoder::ParseUserDefineType<goodcoder::UserType>();
        _parse_user_type->set_user_function(&user_function);
    }

    virtual void TearDown() {
        delete _parse_user_type;
    }

private:
    goodcoder::ParseUserDefineType<goodcoder::UserType> *_parse_user_type;
};

TEST_F(TestParseUserDefineTypeSuite, test_parse_user_define_type) {
    goodcoder::UserType user_type;
    std::string test_data = "123|1.23|a";
    _parse_user_type->parse_user_define_type(test_data, &user_type);
    ASSERT_EQ(123, user_type.int_val);
    ASSERT_EQ(1.23, user_type.double_val);
    ASSERT_EQ('a', user_type.char_val);
}
