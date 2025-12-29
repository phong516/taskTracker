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
        json p_json {
            {"tasks", {}},
            {"next_id", 1}
        };
    public:
        explicit storage(const std::string& filepath = DEFAULT_FILEPATH): p_filepath(filepath) {};
        json load(void) const;
        bool save(void);
        bool exists(void) const;
        bool init(void);
        bool createDir(void);
        bool createFile(void);
        template <typename T>
        bool checkFile(T& file) const;
};