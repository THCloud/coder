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
 * @brief
 *
 **/

#include "dict_handler.h"

namespace goodcoder {

DictHandler::DictHandler() {
}

DictHandler::~DictHandler() {
}

void DictHandler::split_line(const std::string& line,
                             const std::string& separator) {
    Util::split(line, separator, &_columns);
}

ErrorCode DictHandler::check_valid(int index) {
    int len = _columns.size();
    if (index > len) {
        return INDEX_OUT_OF_RANGE;
    }
    std::string value = _columns[index];
    if (value.empty()) {
        return IS_EMPTY_STR;
    }
    return OK;
}

} // namespace goodcoder
