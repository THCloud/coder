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
#include "dict_handler.h"
#include "user_define_type.h"

int main(int argc, char** argv) {
    std::string opt_string = "f:h";
    char option = '\0';

    std::string input_file;

    while ((option = getopt(argc, argv, opt_string.c_str())) != -1) {
        switch (option) {
            case 'f':
                input_file = optarg;
                break;
            case 'h':
                LOG_INFO("Usage: ./dict_parse_demo -f <file_name>");
                exit(EXIT_SUCCESS);
            default:
                LOG_INFO("Usage: ./dict_parse_demo -f <file_name>");
                exit(EXIT_SUCCESS);
        }
    }
    if (input_file.empty()) {
        LOG_INFO("Usage: ./dict_parse_demo -f <file_name>");
        exit(EXIT_FAILURE);
    }

    std::ifstream input_fstream(input_file);
    std::string line;
    goodcoder::ErrorCode ret = goodcoder::OK;
    goodcoder::DictHandler dict_handler;

    goodcoder::ParseUserDefineType<goodcoder::UserType> user_type_parser;
    user_type_parser.set_user_function(&goodcoder::user_function);

    while (std::getline(input_fstream, line)) {
        dict_handler.split_line(line, " ");

        int int_val = 0;
        ret = dict_handler.get_value<int>(0, &int_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get int value is " << int_val << std::endl;

        char char_val = 0;
        ret = dict_handler.get_value<char>(1, &char_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get char value is " << char_val << std::endl;

        double double_val = 0;
        ret = dict_handler.get_value<double>(2, &double_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get double value is " << double_val << std::endl;

        char* str_val = NULL;
        ret = dict_handler.get_value<char*>(3, &str_val);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get str value is " << str_val << std::endl;

        char *arr_val = NULL;
        ret = dict_handler.get_value_array<char>(4, &arr_val);
        if (ret != goodcoder::OK) {
            continue;
        }

        goodcoder::UserType user_type;
        ret = dict_handler.get_user_define_type<goodcoder::UserType>(5, &user_type);
        if (ret != goodcoder::OK) {
            continue;
        }
        std::cout << "get user type value is {" << std::endl
                  << user_type.int_val << std::endl
                  << user_type.double_val << std::endl
                  << user_type.char_val << std::endl
                  << "}" << std::endl;
    }

    return 0;
}
