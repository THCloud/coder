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
 * @brief
 *
 **/

#include <glog/logging.h>

#include "user_define_type.h"

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

void get_typelist(const std::string& type_file,
                  std::vector<std::string>& typelist) {
    // get dict struct from target file. Read the type_file
    // line by line, and save the type to typelist.
    // for more detail of type_file, look at the statements of header file.
    LOG(INFO) << "target file name that saved dict struct: " << type_file;

    std::ifstream type_fstream(type_file);
    std::string type;
    while (std::getline(type_fstream, type)) {
        LOG(INFO) << "get type: " << type;
        typelist.push_back(type);
    }
    type_fstream.close();
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
            LOG(INFO) << "get int value is " << int_val << std::endl;
        }
    } else if (type.compare("float") == 0) {
        float float_val = 0.0f;
        ret = dict_handler.get_value<float>(column, &float_val);
        if (ret == goodcoder::OK) {
            LOG(INFO) << "get float value is " << float_val << std::endl;
        }
    } else if (type.compare("char*") == 0) {
        char* str_val = new char[256];
        ret = dict_handler.get_value<char*>(column, &str_val);
        if (ret == goodcoder::OK) {
            LOG(INFO) << "get str value is " << str_val << std::endl;
        }
        delete str_val;
    } else if (type.compare("Array[char]") == 0) {
        std::vector<char> arr_val;
        ret = dict_handler.get_value<char>(column, arr_val);
        if (ret == goodcoder::OK) {
            LOG(INFO) << "get arrary value is ";
            for (std::size_t i = 0; i < arr_val.size(); ++i) {
                LOG(INFO) << arr_val[i] << " ";
            }
        }
    } else if (type.compare("UserType") == 0) {
        UserType* user_type = new UserType();
        ret = dict_handler.get_user_define_type<UserType>(column,
                                                          user_type,
                                                          &user_function);
        if (ret == goodcoder::OK) {
            LOG(INFO) << "get user type value is {" << std::endl
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
