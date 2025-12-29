#pragma once

#include <iostream>
#include "model/task.h"
#include "view/taskview.h"
#include "model/taskmanager.h"

class commandHandler
{
private:
    taskManager model{};
    taskView view{};

public:
    commandHandler(taskManager model, taskView view) : model(model), view(view) {}
    void cli(int argc, char *argv[]);
};