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
 *
 * @brief  unit test for dict_handler.h
 *
 **/

#include <gtest/gtest.h>
#include "dict_handler.h"
#include "user/user_define_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestDictHandlerSuite : public ::testing::Test {
public:
    TestDictHandlerSuite() : _dict_handler(nullptr) {}
    virtual ~TestDictHandlerSuite() {}

    virtual void SetUp() {
        _dict_handler = new goodcoder::DictHandler();
    }

    virtual void TearDown() {
        if (_dict_handler != nullptr) {
            delete _dict_handler;
        }
        _dict_handler = nullptr;
    }

public:
    goodcoder::DictHandler* _dict_handler;
};

TEST_F(TestDictHandlerSuite, test_split_line) {
    std::string str = "test split function.";
    std::vector<std::string> val_vec;
    goodcoder::DictHandler::split_line(str, " ", val_vec);
    ASSERT_EQ(3, val_vec.size());
}

TEST_F(TestDictHandlerSuite, test_split_with_empty_string) {
    std::string str = "";
    std::vector<std::string> val_vec;
    goodcoder::DictHandler::split_line(str, " ", val_vec);
    ASSERT_EQ(1, val_vec.size());
}

TEST_F(TestDictHandlerSuite, test_split_with_unexpect_string) {
    std::string str = ",,,";
    std::vector<std::string> val_vec;
    goodcoder::DictHandler::split_line(str, ",", val_vec);
    ASSERT_EQ(4, val_vec.size());
}

TEST_F(TestDictHandlerSuite, test_get_value) {
    int int_val = 0;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<int>("1", &int_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(1, int_val);

    float float_val = 0.0f;
    ret = _dict_handler->get_value<float>("1.23", &float_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_NEAR(1.23, float_val, 0.001);

    char* str_val = new char[256];
    ret = _dict_handler->get_value<char*>("hello", &str_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_STREQ("hello", str_val);
    delete str_val;
}

TEST_F(TestDictHandlerSuite, test_get_value_with_unexpect_string) {
    int int_val = 0;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<int>("a", &int_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(0, int_val);

    float float_val = 0.0f;
    ret = _dict_handler->get_value<float>("a", &float_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_NEAR(0, float_val, 0.001);
}

TEST_F(TestDictHandlerSuite, test_get_value_array) {
    std::string test_data = "a,b,c";

    std::vector<char> arr_val;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<char>(test_data, arr_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ('a', arr_val[0]);
    ASSERT_EQ('b', arr_val[1]);
    ASSERT_EQ('c', arr_val[2]);
}

TEST_F(TestDictHandlerSuite, test_get_unexpect_array) {
    std::string test_data = "1,a,2";
    std::vector<int> arr_val;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_value<int>(test_data, arr_val);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(1, arr_val[0]);
    ASSERT_EQ(0, arr_val[1]);
    ASSERT_EQ(2, arr_val[2]);
}

TEST_F(TestDictHandlerSuite, test_get_user_define_type) {
    std::string test_data = "1|1.23|a";

    user::UserType user_type;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_user_define_type<user::UserType>(test_data,
                            &user_type, &user::user_function);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(1, user_type.int_val);
    ASSERT_NEAR(1.23, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);
}

TEST_F(TestDictHandlerSuite, test_get_user_define_type_with_unexpect_string) {
    std::string test_data = "a|a|a";

    user::UserType user_type;
    goodcoder::ErrorCode ret;
    ret = _dict_handler->get_user_define_type<user::UserType>(test_data,
                            &user_type, &user::user_function);
    ASSERT_EQ(goodcoder::OK, ret);
    ASSERT_EQ(0, user_type.int_val);
    ASSERT_NEAR(0, user_type.float_val, 0.001);
    ASSERT_EQ('a', user_type.char_val);

    test_data = "a|a|a|a|a|a|a";

    ret = _dict_handler->get_user_define_type<user::UserType>(test_data,
                            &user_type, &user::user_function);
    ASSERT_EQ(goodcoder::TYPE_NOT_MATCH, ret);
}
