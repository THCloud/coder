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

namespace goodcoder {

class ParseBaseType {
public:
    ParseBaseType();
    ~ParseBaseType();

    template <typename T>
    void parse_column_to_base(const std::string& column, T* result);

    template <typename T>
    void parse_column_to_base_array(const std::string& column, T** result);
};

} // namespace goodcoder

#endif // C_GOODCODER_PARSE_BASE_TYPE_H
