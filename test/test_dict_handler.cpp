/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/



 /**
 * @file   test_dict_handler.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/27 13:19:44
 * @brief
 *
 **/

#include <gtest/gtest.h>
#include "dict_handler.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestDictHandlerSuite : public ::testing::Test {
public:
    TestDictHandlerSuite() {}
    virtual ~TestDictHandlerSuite() {}

    virtual void SetUp() {
        _dict_handler = new goodcoder::DictHandler();
        std::string test_data = "1\t1.23\thello\ta,b,c";
        _dict_handler->split_line(test_data, "\t");
    }

    virtual void TearDown() {
        delete _dict_handler;
    }

public:
    goodcoder::DictHandler* _dict_handler;
};

TEST_F(TestDictHandlerSuite, test_get_value) {
    int int_val = 0;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<int>(0, &int_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(1, int_val);

    float float_val = 0.0;
    ret = _dict_handler->get_value<float>(1, &float_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_NEAR(1.23, float_val, 0.001);

    char* str_val = new char[256];
    ret = _dict_handler->get_value<char*>(2, &str_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_STREQ("hello", str_val);
    delete str_val;
}

TEST_F(TestDictHandlerSuite, test_get_value_array) {
    char* arr_val = NULL;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value_array<char>(3, &arr_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ('a', arr_val[0]);
    ASSERT_EQ('b', arr_val[1]);
    ASSERT_EQ('c', arr_val[2]);
}
