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
 * @brief
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

    ParseUserDefineType(UserFunc func) {
        _s_func = func;
    }
    ~ParseUserDefineType() {}

    ErrorCode parse_user_define_type(const std::string& str, T* result) {
        ErrorCode ret = _s_func(str, result);
        return OK;
    }

    // void set_user_function(ParseUserDefineType<T>::UserFunc func) {
    //     ParseUserDefineType<T>::_s_has_func = true;
    //     _s_func = func;
    // }

private:
    // static bool _s_has_func;
    UserFunc _s_func;
};

// template <typename T>
// bool ParseUserDefineType<T>::_s_has_func = false;


// template <typename T>
// void ParseUserDefineType<T>::set_user_function(ParseUserDefineType<T>::UserFunc func) {
// }

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_USER_DEFINE_TYPE_H
