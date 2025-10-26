#include "json.h"

json::json(std::string string)
{
    std::cout << string << std::endl;
}


json::json(const std::string & filePath)
{
    std::ifstream file(filePath);
    std::string line {};

    while (std::getline(file, line))
    {
       parsedJson.append(line); 
    }
}

jsonValue json::parseNum(const std::string & text, std::string::iterator start, std::string::iterator end)
{
    std::string substr = text.substr(start - text.begin(), end - start);
    size_t dotIdx = substr.find('.');
    if (dotIdx >= (end - start))
    {
        return jsonValue(std::stoi(substr));
    }
    else
    {
        return jsonValue(std::stof(substr));
    }
}

jsonValue json::parseStr(const std::string & text)
{
    return jsonValue(text);
}

void json::parse(const std::string & text)
{
    for (char c : text)
    {
        if (c == '\n')
        {
            continue;
        }
        //TODO continue ' ' but it maybe also inside a string
    }
}