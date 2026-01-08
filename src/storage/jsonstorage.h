#pragma once
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#define DEFAULT_FILEPATH "./data/task.json"
#define DEFAULT_INDENT 2
using json = nlohmann::json;

class storage 
{
    private:
        std::string p_filepath {};
        json p_json {};

        bool exists(void) const;
        bool createDir(void);

    public:
        explicit storage(const std::string& filepath = DEFAULT_FILEPATH): p_filepath(filepath) {};
        json load(void) const;
        bool save(json input);
        bool init(void);
};