#include "model/taskmanager.h"

taskManager::taskManager(const std::string& filepath): p_storage(filepath)
{
    p_storage.init();
    load_tasks_from_json(p_storage.load());
}


json taskManager::task_to_json(void)
{
    json data = json::object();
    data["next_id"] = p_nextID;
    data["tasks"] = json::object(); 
    for (const auto& [id, task]: p_tasks)
    {
        data["tasks"][std::to_string(id)] =
        {
            {"description", task.description},
            {"status", task.status},
            {"createdAt", task.createdAt},
            {"updatedAt", task.updatedAt}
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

    if (!inputJson.is_object())
    {
        std::cerr << "Error: Input Json is not a object\n";
        return;
    }

    if (!inputJson.contains("next_id"))
    {
        std::cerr << "Error: Input Json is missing 'next_id' field\n";
    }
    if (!inputJson.contains("tasks"))
    {
        std::cerr << "Error: Input Json is missing 'tasks' field\n";
        return;
    }
    p_nextID = inputJson["next_id"];
    for (const auto& [id, input_task]: inputJson["tasks"].items())
    {
        Task task {};
        task.id = std::stoi(id);
        task.description = input_task["description"];
        task.status = input_task["status"];
        task.createdAt = input_task["createdAt"];
        task.updatedAt = input_task["updatedAt"];
        
        p_tasks[task.id] = task;
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
    save();
    return true;
}

bool taskManager::update_desc(int id, const std::string& desc)
{
    if (p_tasks.count(id) == 0)
    {
        std::cerr << "Task #" << id << " does not exist\n";
        return false;
    }
    p_tasks[id].description = desc;
    save();
    return true;
}

bool taskManager::update_status(int id, const std::string& status)
{
    if (p_tasks.count(id) == 0)
    {
        std::cerr << "Task #" << id << " does not exist\n";
        return false;
    }
    p_tasks[id].status = status;
    save();
    return true;
}

std::vector<Task> taskManager::list_task(void)
{
    std::vector<Task> tasks {};
    for (const auto& [id, task]: p_tasks)
    {
        tasks.push_back(task);
    }
    return tasks;
}

// tasks -> json -> save
bool taskManager::save(void)
{
    return p_storage.save(task_to_json());
}
