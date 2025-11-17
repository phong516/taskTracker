#include "json.h"

std::map<char, char> brackets = 
{
    {']', '['},
    {'}', '{'}
};

json::json(const std::string & filePath)
{
    std::ifstream file(filePath);
    std::string line {};

    while (std::getline(file, line))
    {
       parsedJson.append(line); 
    }
    rawJson(parsedJson);
    if (*parsedJson.begin() != '{' && *parsedJson.end() != '}')
    {
        std::runtime_error("Invalid json begin and end!!!");
    }
}

jsonValue json::parseNum(const std::string & text, std::size_t start, std::size_t end)
{
    std::string substr = text.substr(start, end - start);
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
    bool isParsing, keyDetected {false};
    if (isValid(text) == false)
    {
        std::cout << "json is invalid\n";
        return false;
    }
    for (std::string::const_iterator it = text.begin(); it != text.end(); it++)
    {
        char c = *it;

        if (it == text.begin() == '{' || it == text.end() == '}')
        {
            continue;
        }
        if (c == '"' && !keyDetected)
        {
            std::string::const_iterator blockEnd = findClosedBracket(c, it, text.end());
            if (std::find(it, blockEnd, ' ') == blockEnd)
            {
                throw std::runtime_error("Invalid Key with \' \'");
                return false;
            }
        }

        if (c == '{' || c == '[')
        {
            std::string::const_iterator blockEnd = findClosedBracket(c, it, text.end());
            if (!handle(c, it, blockEnd))
            {
                std::runtime_error("json error!!!");
                return false;
            }
            it = blockEnd;
        }
    }
    return true;
}

bool json::isValid(const std::string & text)
{
    if (*text.begin() != '{' && *text.end() != '}')
    {
        std::runtime_error("Invalid json begin and end!!!");
        return false;
    }
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
                std::cout << "Parenthesis not balanced!!!";
                return false;
            }
        }
    }
    return bracketStack.empty();
}

std::string::const_iterator json::findClosedBracket(char bracket, std::string::const_iterator begin, std::string::const_iterator end)
{
    if (bracket != *begin)
    {
        std::runtime_error("findclosedBracket: bracket is not match with begin");
        return static_cast<std::string::const_iterator>(NULL);
    }
    std::string::const_iterator closedBracketIte {};
    std::stack<char> bracketStack {};
    for (std::string::const_iterator it = begin; it != end; ++it)
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
                    break;
                }
            }
        }
    }
    return closedBracketIte;
}

bool json::handle(char bracket, std::string::const_iterator begin, std::string::const_iterator end)
{
    switch (bracket)
    {
        case '{':
            return handleObject(begin, end);
        case '[':
            return handleArray(begin, end);
        default:
            return false;
    }
}


bool json::handleObject(std::string::const_iterator begin, std::string::const_iterator end)
{
    [[maybe_unused]] auto _begin = begin;
    [[maybe_unused]] auto _end   = end;
    return true;
}

bool json::handleArray(std::string::const_iterator begin, std::string::const_iterator end)
{
    [[maybe_unused]] auto _begin = begin;
    [[maybe_unused]] auto _end   = end;
    return true;
}

void json::rawJson(std::string & text)
{
    // the idea of this method is to write inplace each character to the text itself, and do not write the space chars outside double quotes ""
    std::string::size_type writePos {0};
    std::string::size_type readPos {0};
    bool insideQuotes {false};
    while (readPos < text.size())
    {
        if (text[readPos] == '"')
        {
            std::string::size_type backPos {readPos};
            // find how many consecutive '\\' (only 1 \) = readPos - backPos
            while (readPos > 0 && text[backPos - 1] == '\\')
            {
                --backPos;
            }
            // if number of slash is even 0, 2, 4, ... -> '\\' = 1 \ -> '\\\\' = 2 \ => this slash is not related to the quote "
            // if number of slash is odd 1, 3, 5, ... -> the last \ is to represent the slash 
            if (readPos - backPos % 2 == 0)
            {
                insideQuotes = !insideQuotes;
            }
        }
     
        //only rewrite if inside quotes or not space chars
        if (insideQuotes || (text[readPos] != '"' && !std::isspace(static_cast<unsigned char>(text[readPos]))))
        {
            text[writePos++] = text[readPos];
        }
        ++readPos;
    }
    text.resize(writePos);
}
