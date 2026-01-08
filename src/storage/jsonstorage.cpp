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
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << p_filepath;
        return false;
    }
    file << p_json.dump(DEFAULT_INDENT);
    file.close();
    return true;
}

bool storage::save(json input)
{
    std::ofstream file(p_filepath, std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << p_filepath << std::endl;
        return false;
    }
    file << input.dump(DEFAULT_INDENT);
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

bool storage::update(const std::string& id, const std::string& field, const std::string& content)
{
    if (!p_json["tasks"].contains(id))
    {
        std::cerr << "ID " + id << " not exists\n";
        return false;
    }
    p_json["tasks"][id][field] = content;
    return true;
}

bool storage::add(const std::string& desc)
{
    int nextID = p_json["next_id"];
    json newJson {
    {
        {"desc", desc},
        {"status", "in-progress"}
    }};
    p_json["tasks"][std::to_string(nextID)] = newJson;
    p_json["next_id"] = ++nextID;
    return true;
}

bool storage::remove(const std::string& id)
{
    p_json["tasks"].erase(id);
    return true;
}

std::vector<json> storage::list(void) const
{
    std::vector<json> taskList {};
    for (auto task: p_json["tasks"])
    {
        taskList.push_back(task);
    }
    return taskList;
}
