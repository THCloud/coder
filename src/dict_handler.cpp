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
        if (!type.empty()) {
            typelist.push_back(type);
        }
    }
    type_fstream.close();
}

void DictHandler::print_error_info(ErrorCode error_code) {
    switch (error_code) {
        case TYPE_NOT_MATCH: {
            LOG(ERROR) << "ErrorInfo: target parse data is not match target parse type";
            break;
        }
        case TYPE_NOT_FOUND: {
            LOG(ERROR) << "ErrorInfo: didn't found matched parse type.";
            break;
        }
        case IS_EMPTY_STR: {
            LOG(ERROR) << "ErrorInfo: target access data value is an empty string";
            break;
        }
        case INDEX_OUT_OF_RANGE: {
            LOG(ERROR) << "ErrorInfo: target access index is out of range.";
            break;
        }
        case MEMORY_ERROR: {
            LOG(ERROR) << "ErrorInfo: error when alloc memory to ptr.";
            break;
        }
        case COLUMN_NUM_NOT_MATCH: {
            LOG(ERROR) << "ErrorInfo: source data's columns is not matched target columns.";
            break;
        }
        case OK: {
            break;
        }
        default: {
            break;
        }
    }
}

} // namespace goodcoder
