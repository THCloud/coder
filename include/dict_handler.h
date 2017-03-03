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
 * @brief
 *
 **/

#ifndef C_GOODCODER_DICT_HANDLER_H
#define C_GOODCODER_DICT_HANDLER_H

#include <string>

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
     *          this is the first step to parse the dict, and will
     *          save each column of line in private variable.
     * @param   <line>        [in]   target line.
     * @param   <separator>   [in]   target separator.
     * @return  null.
     **/
    void split_line(const std::string& line,
                    const std::string& separator);

    /**
     * @brief   parse the target index column to specified type.
     * @param   <index>        [in]  target index of column.
     *          <value>        [out] the specified type value of column.
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     *          INDEX_OUT_OF_RANGE: target index is invalid. (input error)
     *          IS_EMPTY_STR:       target index column is empty. (input error)
     **/
    template <typename T>
    ErrorCode get_value(int index, T* value) {
        ErrorCode is_valid = check_valid(index);
        if (is_valid != OK) {
            return is_valid;
        }

        ParseBaseType *parser = new ParseBaseType();
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        parser->parse_column_to_base<T>(_columns[index], value);
        free(parser);

        return OK;
    }

    /**
     * @brief   parse the target index column to built-in array.
     * @param   <index>        [in]  target index of column.
     *          <value>        [out] the target array of specified type.
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     *          INDEX_OUT_OF_RANGE: target index is invalid. (input error)
     *          IS_EMPTY_STR:       target index column is empty. (input error)
     **/
    template <typename T>
    ErrorCode get_value_array(int index, T** value) {
        ErrorCode is_valid = check_valid(index);
        if (is_valid != OK) {
            return is_valid;
        }

        ParseBaseType *parser = new ParseBaseType();
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        parser->parse_column_to_base_array<T>(_columns[index], value);
        free(parser);

        return OK;
    }

    /**
     * @brief   parse the target index column to user define type.
     * @param   <index>        [in]  target index of column.
     *          <value>        [out] the target of user define type.
     *          <func>         [in]  user specified parse function.
     * @return  Errorcode:
     *          OK:                 parse success.
     *          MEMORY_ERROR:       memory error when new the ptr. (program error)
     *          INDEX_OUT_OF_RANGE: target index is invalid. (input error)
     *          IS_EMPTY_STR:       target index column is empty. (input error)
     **/
    template <typename T>
    ErrorCode get_user_define_type(int index,
                                   T* value,
                                   typename ParseUserDefineType<T>::UserFunc func) {
        ErrorCode is_valid = check_valid(index);
        if (is_valid != OK) {
            return is_valid;
        }

        ParseUserDefineType<T> *parser = new ParseUserDefineType<T>(func);
        if (parser == nullptr) {
            return MEMORY_ERROR;
        }

        ErrorCode ret = parser->parse_user_define_type(_columns[index], value);
        free(parser);

        return ret;
    }

private:

    /**
     * @brief   check whether the target index is valid.
     * @param   <index>       [in]   target index of column.
     * @return  ErrorCode:
     *          OK:                 the index and the value is valid.
     *          IS_EMPTY_STR:       the column is an empty str.
     *          INDEX_OUT_OF_RANGE: the index is not valid.
     **/
    ErrorCode check_valid(int index);

private:

    /**
     * @brief   storage each column of the dict.
     */
    std::vector<std::string> _columns;
};

} // namespace goodcoder

#endif // C_GOODCODER_DICT_HANDLER_H
