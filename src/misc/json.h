#include <iostream>
#include <fstream>
#include <map>
#include <variant>
#include <vector>
#include <stack>

    struct jsonValue;

    using jsonArray = std::vector<jsonValue>;
    using jsonObject = std::map<std::string, jsonValue>;

    struct jsonValue
    {
        using valueType = std::variant<
            std::nullptr_t,
            bool,
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

std::map<char, char> brackets = 
{
    {']', '['},
    {'}', '{'}
};

class json
{
    public:
        json(const std::string jsonStr): parsedJson(std::move(jsonStr)) {}
        json(const std::string & filePath);
        //TODO add operator [] for object key
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
        std::string parsedJson;
        jsonValue parseNum(const std::string & text, std::string::iterator start, std::string::iterator end);
        jsonValue parseStr(const std::string & text);
        bool parse(const std::string & text);
        bool isValid(const std::string & text);
        std::string::const_iterator findClosedBracket(const std::string & text, char bracket, std::string::const_iterator begin, std::string::const_iterator end);
        void handle(const std::string & text, char bracket, std::string::const_iterator begin, std::string::const_iterator end);
        void handleObject(const std::string & text, std::string::const_iterator begin, std::string::const_iterator end);
        void handleArray(const std::string & text, std::string::const_iterator begin, std::string::const_iterator end);
};