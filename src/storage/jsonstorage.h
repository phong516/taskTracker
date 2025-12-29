#pragma once
#include "nlohmann/json.hpp"
#include <fstream>
#define DEFAULT_FILEPATH "./data/task.json"
using json = nlohmann::json;

class storage 
{
    private:
        std::string p_filepath {};
        json p_json {};
    public:
        explicit storage(const std::string& filepath = DEFAULT_FILEPATH): p_filepath(filepath) {};
        json load(void) const;
        bool save(void);
        bool exists(void) const;
        bool init(void);
        bool createDir(void);
        template <typename T>
        bool isFileValid(T& file) const;
};