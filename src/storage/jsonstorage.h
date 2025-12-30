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
        json p_json = json::parse(R"(
        {
            "tasks": {
                "1": {"desc": "description 1", "status": "in-progress"},
                "2": {"desc": "description 2", "status": "done"}},
            "next_id": 3
        }
        )");

        bool exists(void) const;
        bool createDir(void);

        template <typename T>
        bool checkFile(T& file) const;

    public:
        explicit storage(const std::string& filepath = DEFAULT_FILEPATH): p_filepath(filepath) {};
        json load(void) const;
        bool save(void);
        bool init(void);
        bool update(const std::string& id, const std::string& field, const std::string& content);
        bool add(const std::string& desc);
        bool remove(const std::string& id);
        std::vector<json> list(void) const;
};