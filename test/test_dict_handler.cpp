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
    return RUN_ALL_TESTS;
}

class TestDictHandlerSuite : public ::testing::Test {
public:
    TestDictHandlerSuite() {}
    virtual ~TestDictHandlerSuite() {}

    virtual void SetUp() {
        _dict_handler = new goodcoder::DictHandler();
        std::string test_data = "1\t1.23\ta\tstring\ta,b,c";
        _dict_handler->split_line(test_data, "\t");
    }

    virtual void TearDown() {
        delete _dict_handler;
    }

private:
    goodcoder::DictHandler _dict_handler;
};

TEST_F(TestDictHandlerSuite, test_get_value) {
    int int_val = 0;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<int>(0, &int_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(1, int_val);

    double double_val = 0.0;
    ret = _dict_handler->get_value<double>(1, &double_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_NEAR(1.23, double_val, 0.001);

    char char_val;
    ret = _dict_handler->get_value<char>(2, &char_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ('a', char_val);

    char* str_val = NULL;
    ret = _dict_handler->get_value<char*>(3, &str_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_STREQ("string", str_val);
}

TEST_F(TestDictHandlerSuite, test_get_value_array) {
    char* arr_val = NULL;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<char>(4, &arr_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ('a', arr_val[0]);
    ASSERT_EQ('b', arr_val[1]);
    ASSERT_EQ('c', arr_val[2]);
}
