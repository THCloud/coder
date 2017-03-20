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
 *
 * @brief  parse base type to value like int, float, char.
 *
 **/

#ifndef C_GOODCODER_PARSE_BASE_TYPE_H
#define C_GOODCODER_PARSE_BASE_TYPE_H

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "util.h"

namespace goodcoder {

class ParseBaseType {
public:
    ParseBaseType() {}
    ~ParseBaseType() {}

    /**
     * @brief   parse the target column to specified type.
     * @param   <column>       [in]   the value of the column.
     *          <result>       [out]  the target ptr of array. this should be a ptr.
     * @return  null.
     **/
    template <typename T>
    void parse_column_to_base(const std::string& column, T* result) {
        std::stringstream ss;
        ss << column;
        ss >> *result;
    }

    /**
     * @brief   parse the target column to array. use vector.
     * @param   <column>       [in]   the value of the column.
     *          <result>       [out]  target vector to output.
     *          <separator>    [in]   separator of the column. default is ",".
     * @return  null.
     **/
    template <typename T>
    void parse_column_to_base(const std::string& column,
                              std::vector<T>& result,
                              const std::string& separator = ",") {
        std::vector<std::string> tmp_vec;
        Util::split(column, separator, tmp_vec);
        for (std::size_t i = 0; i < tmp_vec.size(); ++i) {
            std::stringstream ss;
            T tmp_t;
            ss << tmp_vec[i];
            ss >> tmp_t;
            result.push_back(tmp_t);
        }
    }
};

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_BASE_TYPE_H
