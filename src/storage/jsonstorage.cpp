#include "jsonstorage.h"
#include <filesystem>

json storage::load(void) const
{
    std::ifstream file(p_filepath, std::ios::in); 
    checkFile(file);
    if (!json::accept(file))
    {
        throw std::runtime_error("json file is invalid " + p_filepath);
        return json {};
    }
    else
    {
        file.clear();
        file.seekg(0, std::ios::beg);
    }
    json loadJson {json::parse(file)};
    file.close();
    return loadJson;
}

bool storage::save(void)
{
    std::ofstream file(p_filepath, std::ios::trunc);
    checkFile(file);
    file << p_json.dump(DEFAULT_INDENT);
    file.close();
    return true;
}

bool storage::exists(void) const
{
    return std::filesystem::exists(p_filepath);
}

bool storage::init(void)
{
    if (!exists())
    {
        createDir();
        save();
    }
    else
    {
        load();
    }
    return true;
}

bool storage::createDir(void)
{
    try
    {
        std::filesystem::create_directories(std::filesystem::path(p_filepath).parent_path());
    }
    catch (std::filesystem::filesystem_error const& ex)
    {
        throw std::runtime_error(ex.what());
        return false;
    }
    return true;
}


template <typename T>
bool storage::checkFile(T& file) const
{
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + p_filepath);
        return false;
    }
    return true;
}