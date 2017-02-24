/***********************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 ***********************************************************************/



 /**
 * @file   parse_base_type.h
 * @author Haoran Li
 * @email  lihaoran02@baidu.com
 * @date   2017/02/24 11:23:30
 * @brief
 *
 **/

#ifndef C_GOODCODER_PARSE_BASE_TYPE_H
#define C_GOODCODER_PARSE_BASE_TYPE_H

#include <sstream>
#include <string>

namespace goodcoder {

class ParseBaseType {
public:
    ParseBaseType();
    ~ParseBaseType();

    template <typename T>
    void parse_column_to_base(const std::string& column, T* result) {
        std::stringstream ss;
        ss << column;
        ss >> *result;
    }

    template <typename T>
    void parse_column_to_base_array(const std::string& column, T** result) {
        std::vector<std::string> tmp_vec;
        boost::split(column, ",", &tmp_vec);
        int count = tmp_vec.size();
        T* tmp_array = new T[count];
        for (int i = 0; i < count; ++i) {
            std::stringstream ss;
            ss << tmp_vec[i];
            ss >> tmp_array[i];
        }
        *result = tmp_array;
    }
};

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_BASE_TYPE_H
