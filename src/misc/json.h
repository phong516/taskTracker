#include <iostream>
#include <fstream>
#include <map>

union jsonValue
{
    int i;
    float f;
    std::map<std::string, jsonValue> * json;
};
struct jsonPair 
{
    std::string key {};
    jsonValue value {};
};

class json
{
    public:
        json(const std::string jsonStr): parsedJson(jsonStr) {}
        json(const std::string & filePath);
    private:
        std::string parsedJson;
        jsonValue parse(const std::string & text, std::string::iterator start, std::string::iterator end);
};