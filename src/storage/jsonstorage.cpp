#include "jsonstorage.h"
#include <filesystem>
#include <string>

json storage::load(void) const
{
    std::ifstream file(p_filepath, std::ios::in); 
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << p_filepath;
        return json {};
    }
    
    if (file.tellg() == 0 && file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "file is empty, so start a new life\n";
        file.close();
        return json {};
    }

    if (!json::accept(file))
    {
        std::cerr << "json file is invalid " << p_filepath << std::endl;
        file.close();
        return json {};
    }
    else
    {
        file.clear();
        file.seekg(0, std::ios::beg);
    }
    json loadJson {json::parse(file)};
    file.close();
    std::cout << p_json.dump(DEFAULT_INDENT);
    return loadJson;
}

bool storage::save(json input)
{
    std::ofstream file(p_filepath, std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << p_filepath << std::endl;
        return false;
    }
    if (!input.empty())
    {
        file << input.dump(DEFAULT_INDENT);
    }
    else
    {
        std::cout << "file is empty\n";
    }
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
        save(json());
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
