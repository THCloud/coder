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
 *
 * @brief  this is a simple demo of dict handler's use.
 *
 **/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <gflags/gflags.h>

#include "dict_handler.h"
#include "user/user_define_type.h"

DEFINE_string(dict_file, "./test_file", "target parse dict file.");
DEFINE_string(type_file, "./typelist", "define dict struct of each line.");

int main(int argc, char** argv) {

    // init gflags.
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::ifstream dict_fstream(FLAGS_dict_file);
    std::string line;
    int line_count = 0;

    std::vector<std::string> typelist;
    // user use get_typelist function to get dict struct,
    // and specify the dict struct in type file. this function
    // will print error info when meet error in type file.
    goodcoder::DictHandler::get_typelist(FLAGS_type_file, typelist);
    goodcoder::ErrorCode ret;

    while (std::getline(dict_fstream, line)) {
        ++line_count;
        std::vector<std::string> columns;
        goodcoder::DictHandler::split_line(line, "\t", columns);

        // skip current line when error, and print error infos.
        if (columns.size() != typelist.size()) {
            ret = goodcoder::COLUMN_NUM_NOT_MATCH;
            goodcoder::Util::print_error_info(ret);
        // jump current line when error, and print error infos.
        if (columns.size() != typelist.size()) {
            ret = goodcoder::COLUMN_NUM_NOT_MATCH;
            goodcoder::DictHandler::print_error_info(ret);
            continue;
        }

        for (std::size_t i = 0; i < typelist.size(); ++i) {
            ret = user::get_value(typelist[i], columns[i]);
            // skip current line when error, and print error infos.
            if (ret != goodcoder::OK) {
                goodcoder::Util::print_error_info(ret);
            // jump current line when error, and print error infos.
            if (ret != goodcoder::OK) {
                goodcoder::DictHandler::print_error_info(ret);
                break;
            }
        }
    }

    return 0;
}
