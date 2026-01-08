#pragma once
#include "storage/jsonstorage.h"
#include "model/task.h"
class taskManager
{
    private:
        std::map<int, Task> p_tasks {};
        int p_nextID {0};
        storage p_storage {}; 
        json task_to_json(void);
        void load_tasks_from_json(const json& inputJson); 
    public:
        taskManager(const std::string& filepath);
        int add_task(const std::string& desc);
        bool delete_task(int id);
        bool update_task(int id, const Task& task);
        std::vector<Task> list_task(void);
        bool save(void);
};