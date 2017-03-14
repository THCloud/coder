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
 * @brief  statements of user-define type and user-define parse function.
 *         and user will parse dict struct here.
 *         this file should be edit by user, and totally controlled by user.
 *         user will only use dict_handler.h to handle his own parse function.
 *
 **/

#ifndef C_GOODCODER_USER_DEFINE_TYPE_H
#define C_GOODCODER_USER_DEFINE_TYPE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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
 * @brief   to parse dict struct file, and save all types in a vector.
 *          type_file should write each column's type to each line.
 *          for example. if target dict struct is :
 *
 *              int    float     char    usertype
 *
 *          then the type_file should be like this:
 *
 *              int
 *              float
 *              char
 *              usertype
 *
 *
 * @param   <type_file>     [in]   target file name that defined dict struct.
 *          <typelist>      [out]  vector to save each type.
 * @return  null.
 **/
void get_typelist(const std::string& type_file,
                  std::vector<std::string>& typelist);
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
