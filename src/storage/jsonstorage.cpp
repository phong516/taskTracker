#include "jsonstorage.h"
#include <filesystem>
#include <iostream>
using json = nlohmann::json;

json storage::load(void) const
{
   std::ifstream file(p_filepath, std::ios::in); 
   if (!isFileValid(file))
   {
        throw std::runtime_error("Failed to open " + p_filepath);
   }
   return json();
}

bool storage::save(void)
{
    return true;
}

bool storage::exists(void) const
{
    return std::filesystem::exists(p_filepath);
}

bool storage::init(void)
{
    return true;
}

bool storage::createDir(void)
{
    return true;
}

template <typename T>
bool storage::isFileValid(T& file) const
{
    if (!file.is_open())
    {
        return false;
    }
    return true;
}