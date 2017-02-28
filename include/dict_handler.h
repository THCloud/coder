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

    void split_line(const std::string& line,
                    const std::string& separator);

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
    ErrorCode check_valid(int index);

private:
    std::vector<std::string> _columns;
};

} // namespace goodcoder

#endif // C_GOODCODER_DICT_HANDLER_H
