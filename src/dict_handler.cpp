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
                             const std::string& separator,
                             std::vector<std::string>& target) {
    Util::split(line, separator, target);
}

} // namespace goodcoder
