/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

 /**
 * @file   dict_handler.h
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 11:01:40
 *
 * @brief  main dict handler class. expose to user.
 *
 **/

#ifndef C_GOODCODER_DICT_HANDLER_H
#define C_GOODCODER_DICT_HANDLER_H

#include <string>
#include <vector>

#include "parse_base_type.h"
#include "parse_user_define_type.h"
#include "util.h"

namespace goodcoder {

class DictHandler {
public:
    DictHandler();
    ~DictHandler();

    /**
     * @brief   split line to part. like split() function in python.
     *          this function is expose to user, to split line to column.
     * @param   <line>        [in]   target line.
     *          <separator>   [in]   target separator.
     *          <target>      [out]  target vector to save the splited.
     * @return  null.
     **/
    static void split_line(const std::string& line,
                           const std::string& separator,
                           std::vector<std::string>& target);

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
    * @param   <type_file>     [in]   target file name that defined dict struct.
    *          <typelist>      [out]  vector to save each type.
    * @return  null.
    **/
    static void get_typelist(const std::string& type_file,
                             std::vector<std::string>& typelist);

    /**
     * @brief   print error info according error code.
     * @param   <error_code>        [in]    target error code.
     * @return  none.
     **/
    static void print_error_info(ErrorCode error_code);

    /**
     * @brief   parse the target index column to specified type.
     * @param   <column>       [in]  target column value.
     *          <value>        [out] the specified type value of column.
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     **/
    template <typename T>
    ErrorCode get_value(const std::string& column, T* value) {
        ParseBaseType *parser = new ParseBaseType();
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        parser->parse_column_to_base<T>(column, value);
        delete parser;

        return OK;
    }

    /**
     * @brief   parse the target index column to array.
     * @param   <column>       [in]  target column value.
     *          <value>        [out] the vector of specified type.
     *          <separator>    [in]  separator of column. default is ",".
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     **/
    template <typename T>
    ErrorCode get_value(const std::string& column,
                        std::vector<T>& value,
                        const std::string& separator = ",") {
        ParseBaseType *parser = new ParseBaseType();
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        parser->parse_column_to_base<T>(column, value, separator);
        delete parser;

        return OK;
    }

    /**
     * @brief   parse the target index column to user define type.
     * @param   <column>       [in]  target column value.
     *          <value>        [out] the target of user define type.
     *          <func>         [in]  user specified parse function.
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     **/
    template <typename T>
    ErrorCode get_user_define_type(const std::string& column,
                                   T* value,
                                   typename ParseUserDefineType<T>::UserFunc func) {
        ParseUserDefineType<T> *parser = new ParseUserDefineType<T>(func);
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        ErrorCode ret = parser->parse_user_define_type(column, value);
        delete parser;

        return ret;
    }

};

} // namespace goodcoder

#endif // C_GOODCODER_DICT_HANDLER_H
