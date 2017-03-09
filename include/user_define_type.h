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

/**
 * @brief   to parse dict struct file, and save all types in a vector.
 * @param   <type_file>     [in]   target file name that defined dict struct.
 *          <typelist>      [out]  vector to save each type.
 * @return  null.
 **/
void get_typelist(const std::string& type_file,
                  std::vector<std::string>& typelist) {
    std::ifstream type_fstream(type_file);
    std::string type;
    while (std::getline(type_fstream, type)) {
        typelist.push_back(type);
    }
    type_fstream.close();
}

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
            std::cout << "get int value is " << int_val << std::endl;
        }
    } else if (type.compare("float") == 0) {
        float float_val = 0.0f;
        ret = dict_handler.get_value<float>(column, &float_val);
        if (ret == goodcoder::OK) {
            std::cout << "get float value is " << float_val << std::endl;
        }
    } else if (type.compare("char*") == 0) {
        char* str_val = new char[256];
        ret = dict_handler.get_value<char*>(column, &str_val);
        if (ret == goodcoder::OK) {
            std::cout << "get str value is " << str_val << std::endl;
        }
        delete str_val;
    } else if (type.compare("Array[char]") == 0) {
        std::vector<char> arr_val;
        ret = dict_handler.get_value<char>(column, arr_val);
        if (ret == goodcoder::OK) {
            std::cout << "get arrary value is ";
            for (std::size_t i = 0; i < arr_val.size(); ++i) {
                std::cout << arr_val[i] << " ";
            }
            std::cout << std::endl;
        }
    } else if (type.compare("UserType") == 0) {
        UserType* user_type = new UserType();
        ret = dict_handler.get_user_define_type<UserType>(column,
                                                          user_type,
                                                          &user_function);
        if (ret == goodcoder::OK) {
            std::cout << "get user type value is {" << std::endl
                      << user_type->int_val << std::endl
                      << user_type->float_val << std::endl
                      << user_type->char_val << std::endl
                      << "}" << std::endl << std::endl;
        }
        delete user_type;
    }
    return ret;
}

} // namespace user

#endif // C_GOODCODER_USER_DEFINE_TYPE_H
