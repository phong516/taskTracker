#include "taskmanager.h"

taskManager::taskManager(const std::string& filepath): p_storage(filepath)
{

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


}

bool taskManager::delete_task(int id)
{

}

bool taskManager::update_task(int id, const Task& task)
{

}

bool taskManager::load(json input) const
{

}

bool taskManager::save(json output)
{

}