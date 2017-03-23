/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   test_util.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/27 12:42:10
 *
 * @brief  unit test for util.h
 *
 **/

#include <gtest/gtest.h>
#include "util.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestUtilSuite : public ::testing::Test {
};

TEST_F(TestUtilSuite, test_split) {
    std::string str = "test split function.";
    std::vector<std::string> val_vec;
    goodcoder::Util::split(str, " ", val_vec);
    ASSERT_EQ(3, val_vec.size());
}

TEST_F(TestUtilSuite, test_split_with_empty_string) {
    std::string str = "";
    std::vector<std::string> val_vec;
    goodcoder::Util::split(str, " ", val_vec);
    ASSERT_EQ(1, val_vec.size());
}

TEST_F(TestUtilSuite, test_split_with_unexpect_string) {
    std::string str = ",,,";
    std::vector<std::string> val_vec;
    goodcoder::Util::split(str, ",", val_vec);
    ASSERT_EQ(4, val_vec.size());
}
