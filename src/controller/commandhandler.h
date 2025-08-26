#pragma once
#include <iostream>
#include "task.h"
#include "taskview.h"
#include "taskmanager.h"

class commandHandler
{
private:
    taskManager model{};
    taskView view{};

public:
    commandHandler(taskManager model, taskView view) : model(model), view(view) {}
    void cli(int argc, char *argv[]);
};