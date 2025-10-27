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

bool json::parse(const std::string & text)
{
    if (isValid(text) == false)
    {
        std::cout << "json is invalid\n";
        return false;
    }
    for (char c : text)
    {
        if (c == '\n' || c == ' ')
        {
            continue;
        }
        //TODO continue ' ' but it maybe also inside a string
        if (c == '{')
        {

        }
    }
}

bool json::isValid(const std::string & text)
{
    std::stack<char> bracketStack {};

    for (char c : text)
    {
        if (c == '{' || c == '[')
        {
            bracketStack.push(c);
        }
        if (c == '}' || c == ']')
        {
            if (bracketStack.empty() == true)
            {
                return false;
            }
            // if top is '[', bracket[c] would be ']'
            if (bracketStack.top() == brackets[c])
            {
                bracketStack.pop();
            }
            else
            {
                return false;
            }
        }
    }
    return bracketStack.empty();
}

std::string::iterator json::findClosedBracket(std::string & text, char bracket, std::string::iterator begin, std::string::iterator end)
{
    std::string::iterator closedBracketIte {};
    std::stack<char> bracketStack {};
    for (std::string::iterator it = begin; it != end; it++)
    {
        char c = *it;
        if (c == '{' || c == '[')
        {
            bracketStack.push(c);
        }
        if (c == '}' || c == ']')
        {
            // if top is '[', bracket[c] would be ']'
            if (bracketStack.top() == brackets[c])
            {
                bracketStack.pop();
                if (bracketStack.empty() == true)
                {
                    closedBracketIte = it;
                }
            }
        }
    }
    return closedBracketIte;
}

void handleObject(const std::string & text, std::string::iterator begin, std::string::iterator end)
{
    
}