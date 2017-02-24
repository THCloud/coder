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

typedef enum {
    OK,
    TYPE_NOT_MATCH,
    IS_EMPTY_STR,
    INDEX_OUT_OF_RANGE,
    MEMORY_ERROR
} ErrorCode;

} // namespace goodcoder

#endif // C_GOODCODER_UTIL_H
