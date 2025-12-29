#pragma once
#include "json.hpp"
using json = nlohmann::json;

class storage 
{
    private:
        std::string p_filepath {};
        json p_json {};
    public:
        explicit storage(const std::string& filepath): p_filepath(filepath) {};
        json load(void) const;
        bool save(void);
        bool exists(void) const;
        bool init(void);
};