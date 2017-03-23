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
 *
 * @brief  common function and constant statement.
 *
 **/

#ifndef C_GOODCODER_UTIL_H
#define C_GOODCODER_UTIL_H

#include <string>
#include <vector>

#define LOG_INFO(fmt, arg...) \
    fprintf(stdout, fmt "\n", ##arg)

#define LOG_ERROR(fmt, arg...) \
    fprintf(stderr, "Errorinfo: file %s line %d -- " fmt "\n", \
        __FILE__, __LINE__, ##arg)

namespace goodcoder {

typedef enum {
    OK,
    TYPE_NOT_MATCH,
    TYPE_NOT_FOUND,
    IS_EMPTY_STR,
    INDEX_OUT_OF_RANGE,
    MEMORY_ERROR,
    COLUMN_NUM_NOT_MATCH
} ErrorCode;

class Util {
public:
    Util();
    ~Util();

    /**
     * @brief   implement of split function like python.
     * @param   <str>         [in]  target split string.
     *          <separator>   [in]  separator.
     *          <ret>         [out] the result vector.
     * @return  null.
     **/
    static void split(const std::string& str,
                      const std::string& separator,
                      std::vector<std::string>& ret);

    /**
    * @brief   print error info according error code.
    * @param   <error_code>        [in]    target error code.
    * @return  none.
    **/
    static void print_error_info(ErrorCode error_code);

};

} // namespace goodcoder

#endif // C_GOODCODER_UTIL_H
