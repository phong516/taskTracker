#include "taskmanager.h"

taskManager::taskManager(const std::string& filepath): p_storage(filepath)
{
    p_storage.init();
    load_tasks_from_json(p_storage.load());
}


json taskManager::task_to_json(void)
{
    json data {};
    data["next_id"] = p_nextID;
    data["tasks"] = json::object(); 
    for (const auto& [id, task]: p_tasks)
    {
        data["tasks"][std::to_string(id)] =
        {
            {"description", task.description},
            {"status", task.status},
            {"createdAt", std::to_string(task.createdAt)},
            {"updatedAt", std::to_string(task.updatedAt)}
        };
    }
    return data;
}

void taskManager::load_tasks_from_json(const json& inputJson)
{
    if (inputJson.empty())
    {
        return;
    }
    Task task;
    if (inputJson.contains("next_id"))
    {
        p_nextID = inputJson["next_id"];
    }
    if (inputJson.contains("tasks"))
    {
        for (const auto& [id, task]: inputJson["tasks"].items())
        {
            Task task {};
            task.id = std::stoi(id);
            task.description = inputJson.value("description", "");
            task.status = inputJson.value("status", "");
            task.createdAt = inputJson.value("createdAt", std::time(nullptr));
            task.updatedAt = inputJson.value("updatedAt", std::time(nullptr));
            
            p_tasks[task.id] = task;
        }
    }
}

int taskManager::add_task(const std::string& desc)
{
    Task task;
    task.id = p_nextID++;
    task.description = desc;

    p_tasks[task.id] = task;
    
    save();
    return task.id;
}

bool taskManager::delete_task(int id)
{
    if (p_tasks.count(id) == 0)
    {
        std::cerr << "Task #" << id << " does not exist\n";
        return false;
    }
    p_tasks.erase(id);
    save();
    return true;
}

bool taskManager::update_task(int id, const Task& task)
{
    if (p_tasks.count(id) == 0)
    {
        std::cerr << "Task #" << id << " does not exist\n";
        return false;
    }
    p_tasks[id] = task;
    return true;
}

// tasks -> json -> save
bool taskManager::save(void)
{
    return p_storage.save(task_to_json());
}
