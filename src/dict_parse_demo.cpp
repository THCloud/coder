/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/



 /**
 * @file   dict_parse_demo.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 19:34:24
 * @brief
 *
 **/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <gflags/gflags.h>

#include "dict_handler.h"
#include "user_define_type.h"

DEFINE_string(file, "./test_file", "target parse dict file.");

int main(int argc, char** argv) {

    google::ParseCommandLineFlags(&argc, &argv, true);

    std::ifstream input_fstream(FLAGS_file);
    std::string line;
    goodcoder::ErrorCode ret = goodcoder::OK;
    goodcoder::DictHandler dict_handler;

    while (std::getline(input_fstream, line)) {
        dict_handler.split_line(line, "\t");

        int int_val = 0;
        ret = dict_handler.get_value<int>(0, &int_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get int value is " << int_val << std::endl;

        float float_val = 0;
        ret = dict_handler.get_value<float>(1, &float_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get float value is " << float_val << std::endl;

        char* str_val = new char[256];
        ret = dict_handler.get_value<char*>(2, &str_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get str value is " << str_val << std::endl;
        delete str_val;

        char *arr_val = NULL;
        ret = dict_handler.get_value_array<char>(3, &arr_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get arrary value is ";
        for (int i = 0; i < sizeof(arr_val) / sizeof(arr_val[0]); i++) {
            std::cout << arr_val[i] << " ";
        }
        std::cout << std::endl;

        goodcoder::UserType user_type;
        ret = dict_handler.get_user_define_type<goodcoder::UserType>(4,
                                                                     &user_type,
                                                                     &goodcoder::user_function);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get user type value is {" << std::endl
                  << user_type.int_val << std::endl
                  << user_type.float_val << std::endl
                  << user_type.char_val << std::endl
                  << "}" << std::endl;
    }

    return 0;
}
