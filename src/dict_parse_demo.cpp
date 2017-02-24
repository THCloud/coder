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

#include "dict_handler.h"

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

    while (std::getline(input_fstream, line)) {
        dict_handler.split_line(line);
    }
}
