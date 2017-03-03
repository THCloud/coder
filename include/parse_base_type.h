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
 * @brief  parse base type like int, double, char.
 *
 **/

#ifndef C_GOODCODER_PARSE_BASE_TYPE_H
#define C_GOODCODER_PARSE_BASE_TYPE_H

#include <sstream>
#include <string>
#include <vector>

#include "util.h"

namespace goodcoder {

class ParseBaseType {
public:
    ParseBaseType() {}
    ~ParseBaseType() {}

    /**
     * @brief   parse the target column to base type.
     *          base type is like int, float, char, and so on.
     * @param   <column>       [in]   the value of the column.
     *          <result>       [out]  the target of specified type.
     * @return  null.
     **/
    template <typename T>
    void parse_column_to_base(const std::string& column, T* result) {
        std::istringstream ss(column);
        ss >> *result;
    }

    /**
     * @brief   parse the target column to built-in array.
     * @param   <column>       [in]   the value of the column.
     *          <result>       [out]  the target ptr of array. this should be a 2d ptr.
     * @return  null.
     **/
    template <typename T>
    void parse_column_to_base_array(const std::string& column, T** result) {
        std::vector<std::string> tmp_vec;
        Util::split(column, ",", &tmp_vec);
        int count = tmp_vec.size();
        T* tmp_array = new T[count];
        for (int i = 0; i < count; ++i) {
            std::istringstream ss(tmp_vec[i]);
            ss >> tmp_array[i];
        }
        *result = tmp_array;
    }
};

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_BASE_TYPE_H
