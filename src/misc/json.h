#include <iostream>
#include <fstream>
#include <map>
#include <variant>
#include <vector>

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
};
class json
{
    public:
        json(const std::string jsonStr): parsedJson(std::move(jsonStr)) {}
        json(const std::string & filePath);
    private:
        std::string parsedJson;
        jsonValue parseNum(const std::string & text, std::string::iterator start, std::string::iterator end);
        jsonValue parseStr(const std::string & text);
        void parse(const std::string & text);
};