/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/



 /**
 * @file   parse_user_define_type.h
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 19:24:56
 * @brief  parse string to user-define type.
 *
 **/

#ifndef C_GOODCODER_PARSE_USER_DEFINE_TYPE_H
#define C_GOODCODER_PARSE_USER_DEFINE_TYPE_H

#include <string>
#include "util.h"

namespace goodcoder {

template <typename T>
class ParseUserDefineType {
public:
    typedef ErrorCode (*UserFunc)(const std::string&, T*);

    /**
     * @brief   constructor.
     * @param   <func>      [in]   the specified parse function that user given.
     * @return  null.
     **/
    ParseUserDefineType(UserFunc func) {
        _s_func = func;
    }
    ~ParseUserDefineType() {}

    /**
     * @brief   parse column to user define type. with user function.
     * @param   <column>         [in]   target column.
     *          <result>         [out]  target user define type. this should be a ptr.
     * @return  ErrorCode:
     *          OK:              parse success.
     *          TYPE_NOT_MATCH:  target column is not math the user define type. (input error)
     *          MEMORY_ERROR:    memory error when new. (program error)
     **/
    ErrorCode parse_user_define_type(const std::string& column, T* result) {
        ErrorCode ret = _s_func(column, result);
        return ret;
    }


private:

    /**
     * @breif the specified parse function that user given.
     */
    UserFunc _s_func;
};

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_USER_DEFINE_TYPE_H
