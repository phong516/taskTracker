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
    private:
        jsonValue rootJson {};
        std::string parsedJson;
        jsonValue parseNum(const std::string & text, std::string::iterator start, std::string::iterator end);
        jsonValue parseStr(const std::string & text);
        bool parse(const std::string & text);
        bool isValid(const std::string & text);
        std::string::iterator findClosedBracket(std::string & text, char bracket, std::string::iterator begin, std::string::iterator end);

};