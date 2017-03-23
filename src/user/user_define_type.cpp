/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/

/**
 * @file   user_define_type.cpp
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/03/14 14:48:22
 *
 * @brief
 *
 **/

#include "user/user_define_type.h"

namespace user {

goodcoder::ErrorCode user_function(const std::string& str, UserType* user_type) {
    std::vector<std::string> data;
    goodcoder::DictHandler *parser = new goodcoder::DictHandler();
    if (parser == nullptr) {
        return goodcoder::MEMORY_ERROR;
    }

    goodcoder::DictHandler::split_line(str, "|", data);
    if (data.size() != 3) {
        return goodcoder::TYPE_NOT_MATCH;
    }

    parser->get_value<int>(data[0], &user_type->int_val);
    parser->get_value<float>(data[1], &user_type->float_val);
    parser->get_value<char>(data[2], &user_type->char_val);

    delete parser;
    return goodcoder::OK;
}

goodcoder::ErrorCode get_value(const std::string& type,
                               const std::string& column) {
    goodcoder::DictHandler dict_handler;
    if (column.empty()) {
        return goodcoder::IS_EMPTY_STR;
    }

    goodcoder::ErrorCode ret = goodcoder::TYPE_NOT_FOUND;
    if (type.compare("int") == 0) {
        int int_val = 0;
        ret = dict_handler.get_value<int>(column, &int_val);
        if (ret == goodcoder::OK) {
            LOG_INFO("get int value is %d", int_val);
        }
    } else if (type.compare("float") == 0) {
        float float_val = 0.0f;
        ret = dict_handler.get_value<float>(column, &float_val);
        if (ret == goodcoder::OK) {
            LOG_INFO("get float value is %lf", float_val);
        }
    } else if (type.compare("char*") == 0) {
        char* str_val = new char[256];
        ret = dict_handler.get_value<char*>(column, &str_val);
        if (ret == goodcoder::OK) {
            LOG_INFO("get str value is %s", str_val);
        }
        delete str_val;
    } else if (type.compare("Array[char]") == 0) {
        std::vector<char> arr_val;
        ret = dict_handler.get_value<char>(column, arr_val);
        if (ret == goodcoder::OK) {
            LOG_INFO("get array value is");
            for (std::size_t i = 0; i < arr_val.size(); ++i) {
                LOG_INFO("%c", arr_val[i]);
            }
        }
    } else if (type.compare("UserType") == 0) {
        UserType* user_type = new UserType();
        ret = dict_handler.get_user_define_type<UserType>(column,
                                                          user_type,
                                                          &user_function);
        if (ret == goodcoder::OK) {
            LOG_INFO("get user type value is {%d, %lf, %c}",
                user_type->int_val, user_type->float_val, user_type->char_val);
        }
        delete user_type;
    }
    return ret;
}

} // namespace user
