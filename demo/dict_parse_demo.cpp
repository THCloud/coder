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
#include <glog/logging.h>

#include "dict_handler.h"
#include "user_define_type.h"

DEFINE_string(dict_file, "./test_file", "target parse dict file.");
DEFINE_string(type_file, "./typelist", "define dict struct of each line.");

int main(int argc, char** argv) {

    // init gflags.
    google::ParseCommandLineFlags(&argc, &argv, true);
    // init glog.
    google::InitGoogleLogging(argv[0]);

    std::ifstream dict_fstream(FLAGS_dict_file);
    std::string line;
    int line_count = 0;

    std::vector<std::string> typelist;
    user::get_typelist(FLAGS_type_file, typelist);
    goodcoder::ErrorCode ret;

    while (std::getline(dict_fstream, line)) {
        ++line_count;
        std::vector<std::string> columns;
        goodcoder::DictHandler::split_line(line, "\t", columns);
        if (columns.size() != typelist.size()) {
            break;
        }

        for (std::size_t i = 0; i < typelist.size(); ++i) {
            ret = user::get_value(typelist[i], columns[i]);
            if (ret != goodcoder::OK) {
                break;
            }
        }
    }

    google::ShutdownGoogleLogging();

    return 0;
}
