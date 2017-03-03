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
           std::vector<std::string>* ret) {
    size_t last = 0;
    size_t index = str.find_first_of(separator, last);
    while (index != std::string::npos) {
        ret->push_back(str.substr(last, index - last));
        last = index + 1;
        index = str.find_first_of(separator, last);
    }
    if (index - last > 0) {
        ret->push_back(str.substr(last, index - last));
    }
}

} // namespace goodcoder