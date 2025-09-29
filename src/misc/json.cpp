#include "json.h"

Json::Json(std::string string)
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

jsonValue parse(const std::string & text, std::string::iterator start, std::string::iterator end)
{
    std::string substr = text.substr(start - text.begin(), end - start);
    size_t dotIndex = substr.find('.');
    if (dotIndex >= (end - start))
    {
        return
        {
            .i = std::stoi(substr)
        };
    }
    else
    {
        return
        {
            .f = std::stof(substr)
        };
    }
}