/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   user_define_type.h
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 11:14:52
 *
 * @brief  statements of user-define type and user-define parse function.
 *         and user will parse dict struct here.
 *         this file should be edit by user, and totally controlled by user.
 *         user will only use dict_handler.h to handle his own parse function.
 *
 **/

#ifndef C_GOODCODER_USER_USER_DEFINE_TYPE_H
#define C_GOODCODER_USER_USER_DEFINE_TYPE_H

#include <string>

#include "dict_handler.h"

namespace user {

/**
 * @brief   user define type.
 **/
struct UserType {
    int int_val;
    float float_val;
    char char_val;
};

/**
 * @brief   parse function that user given.
 * @param   <str>          [in]    target string value.
 *          <user_type>    [out]   target user define type. this should be a ptr.
 * @return
 **/
goodcoder::ErrorCode user_function(const std::string& str, UserType* user_type);

/**
 * @brief   get value with given type and column.
 * @param   <type>        [in]    given specified type.
 *          <column>      [in]    target column value.
 * @return  ErrorCode:
 *          OK:                 parse success.
 *          MEMORY_ERROR:       memory error when new the ptr. (program error)
 *          IS_EMPTY_STR:       target index column is empty. (input error)
 **/
goodcoder::ErrorCode get_value(const std::string& type,
                               const std::string& column);

} // namespace user

#endif // C_GOODCODER_USER_DEFINE_TYPE_H
