/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/



 /**
 * @file   util.h
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 11:03:36
 * @brief
 *
 **/

#ifndef C_GOODCODER_UTIL_H
#define C_GOODCODER_UTIL_H

namespace goodcoder {

#define LOG_INFO(fmt, arg...) \
    printf("\033[1;32m" fmt "\033[0m\n", ##arg)

typedef enum {
    OK,
    TYPE_NOT_MATCH,
    TYPE_NOT_FOUND,
    IS_EMPTY_STR,
    INDEX_OUT_OF_RANGE,
    MEMORY_ERROR
} ErrorCode;

void split(const std::string& str, const std::string& separator,
           std::vector<std::string>* ret) {
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

} // namespace goodcoder

#endif // C_GOODCODER_UTIL_H
