#pragma once

#include <iostream>
#include "view/taskview.h"
#include "model/taskmanager.h"

class commandHandler
{
private:
    taskManager p_model {};
    taskView p_view {};

    void handle_add(const std::vector<std::string>& args);
    void handle_list(const std::vector<std::string>& args);
    void handle_delete(const std::vector<std::string>& args);
    void handle_update(const std::vector<std::string>& args);
    void handle_help(void);

    std::vector<std::string> parse_args(int argc, char* argv[]);
    std::string get_option_value(const std::vector<std::string>& args, const std::string& option) const;
    bool has_option(const std::vector<std::string>& args, const std::string& option) const;

public:
    explicit commandHandler(const std::string& db_path = "data/task.json");
    void execute(int argc, char *argv[]);
};