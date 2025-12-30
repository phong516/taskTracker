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
        bool exists(void) const;
        bool createDir(void);

        template <typename T>
        bool checkFile(T& file) const;

    public:
        explicit storage(const std::string& filepath = DEFAULT_FILEPATH): p_filepath(filepath) {};
        json load(void) const;
        bool save(void);
        bool init(void);
        bool update(const std::string& id, const std::string& desc);
        bool add(const std::string& desc);
        bool remove(const std::string& id);
        std::vector<std::string> list(void) const;
};