/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   dict_handler.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 11:13:14
 *
 * @brief
 *
 **/

#include "dict_handler.h"

#include <fstream>
#include <iostream>

namespace goodcoder {

DictHandler::DictHandler() {
}

DictHandler::~DictHandler() {
}

void DictHandler::split_line(const std::string& line,
                             const std::string& separator,
                             std::vector<std::string>& target) {
    Util::split(line, separator, target);
}

void DictHandler::get_typelist(const std::string& type_file,
                               std::vector<std::string>& typelist) {
    // get dict struct from target file. Read the type_file
    // line by line, and save the type to typelist.
    // for more detail of type_file, look at the statements of header file.
    LOG_INFO("target file name that saved dict struct: %s", type_file.c_str());

    std::ifstream type_fstream(type_file);
    std::string type;
    while (std::getline(type_fstream, type)) {
        LOG_INFO("get type: %s", type.c_str());
        if (!type.empty()) {
            typelist.push_back(type);
        } else {
            LOG_ERROR("empty str in type file. skip the line.");
        }
    }
    type_fstream.close();
}

} // namespace goodcoder
