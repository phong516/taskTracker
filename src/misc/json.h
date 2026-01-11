#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <variant>
#include <vector>
#include <stack>
#include <algorithm>

struct jsonValue;

using jsonArray = std::vector<jsonValue>;
using jsonObject = std::map<std::string, jsonValue>;

struct jsonValue
{
    using valueType = std::variant<
        std::nullptr_t,
        bool,
        int,
        double,
        std::string,
        jsonArray,
        jsonObject
    >;
    valueType value;
    jsonValue() : value(nullptr) {}

    template<typename T> 
    jsonValue(T v) : value(std::move(v)) {}
    //TODO add operator [] for array index
    jsonValue & operator[](const std::string & key)
    {
        if (auto * obj = std::get_if<jsonObject>(&value))
        {
            return (*obj)[key];
        }
        throw std::runtime_error("Not jsonObject");
    }

    const jsonValue & operator[](const std::string & key) const
    {
        if (const auto * obj = std::get_if<jsonObject>(&value))
        {
            return obj->at(key);
        }
        throw std::runtime_error("Not jsonObject");
    }

    jsonValue & operator[](size_t index)
    {
        if (auto * array = std::get_if<jsonArray>(&value))
        {
            return array->at(index);
        }
        throw std::runtime_error("Not jsonArray");
    }

    const jsonValue & operator[](size_t index) const
    {
        if (auto * array = std::get_if<jsonArray>(&value))
        {
            return array->at(index);
        }
        throw std::runtime_error("Not jsonArray");
    }
};

class json
{
    public:
        json(const std::string & filePath);
        jsonValue & operator[](const std::string & key)
        {
            return rootJson[key];
        }
        jsonValue & operator[](size_t index)
        {
            return rootJson[index];
        }
    private:
        jsonValue rootJson {};
        std::string parsedJson {};
        void rawJson(std::string & text);
        jsonValue parseNum(const std::string & text, std::size_t start, std::size_t end);
        std::string parseStr(std::string::const_iterator begin, std::string::const_iterator end);
        jsonValue parse(std::string::const_iterator begin, std::string::const_iterator end);
        jsonValue parseObject(std::string::const_iterator begin, std::string::const_iterator end);
        jsonValue parseArray(std::string::const_iterator begin, std::string::const_iterator end);
        bool isValid(const std::string & text);
        std::string::const_iterator findClosingBracket(char bracket, std::string::const_iterator begin, std::string::const_iterator end);
};