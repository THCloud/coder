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
 * @brief
 *
 **/

#ifndef C_GOODCODER_USER_DEFINE_TYPE_H
#define C_GOODCODER_USER_DEFINE_TYPE_H

#include <string>
#include <vector>

#include "parse_base_type.h"
#include "util.h"

namespace goodcoder {

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
ErrorCode user_function(const std::string& str, UserType* user_type) {
    std::vector<std::string> data;
    Util::split(str, "|", &data);
    if (data.size() != 3) {
        return TYPE_NOT_MATCH;
    }

    ParseBaseType *parser = new ParseBaseType();
    if (parser == nullptr) {
        return MEMORY_ERROR;
    }

    parser->parse_column_to_base<int>(data[0], &user_type->int_val);
    parser->parse_column_to_base<float>(data[1], &user_type->float_val);
    parser->parse_column_to_base<char>(data[2], &user_type->char_val);

    free(parser);
    return OK;
}

} // namespace goodcoder

#endif // C_GOODCODER_USER_DEFINE_TYPE_H
