/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   util.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/28 09:54:44
 *
 * @brief
 *
 **/

#include "util.h"

namespace goodcoder {

Util::Util() {
}

Util::~Util() {
}

void Util::split(const std::string& str, const std::string& separator,
           std::vector<std::string>& ret) {
    size_t last = 0;
    size_t index = str.find_first_of(separator, last);
    while (index != std::string::npos) {
        ret.push_back(str.substr(last, index - last));
        last = index + 1;
        index = str.find_first_of(separator, last);
    }
    if (index - last > 0) {
        ret.push_back(str.substr(last, index - last));
    }
}

void Util::print_error_info(ErrorCode error_code) {
    switch (error_code) {
        case TYPE_NOT_MATCH: {
            LOG_ERROR("target parse data is not match target parse type.");
            break;
        }
        case TYPE_NOT_FOUND: {
            LOG_ERROR("didn't found matched parse type.");
            break;
        }
        case IS_EMPTY_STR: {
            LOG_ERROR("target access data value is an empty string");
            break;
        }
        case INDEX_OUT_OF_RANGE: {
            LOG_ERROR("target access index is out of range.");
            break;
        }
        case MEMORY_ERROR: {
            LOG_ERROR("error when alloc memory to ptr.");
            break;
        }
        case COLUMN_NUM_NOT_MATCH: {
            LOG_ERROR("source data's columns is not matched target columns.");
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
