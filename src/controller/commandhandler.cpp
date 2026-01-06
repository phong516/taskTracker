#include "controller/commandhandler.h"


void commandHandler::handle_add(const std::vector<std::string>& args)
{
    if (args.empty())
    {
        std::cerr << "Error: Description is required\n";
        std::cout << "Usage: tasktracker add <desc>\n";
        return;
    }
    else if (args.size() != 1)
    {
        std::cerr << "Error: Only 1 argument is provided\n";
        std::cout << "Usage: tasktracker add <desc>\n";
        return;
    }
    std::string desc = args[0];
    //int id {p_manager.add_task(desc, "in-progress");
    //std::cout << "Task " << id << " added successfully!\n";
    return;
}
void commandHandler::handle_list(const std::vector<std::string>& args)
{

    return;
}

void commandHandler::handle_delete(const std::vector<std::string>& args)
{
    return;
}

void commandHandler::handle_update(const std::vector<std::string>& args)
{
    return;
}

void commandHandler::handle_help()
{
    std::cout << R"(
    Task Tracker CLI
    USAGE: 
        tasktracker <command> [arguments] [options]
    COMMANDS:
        add <desc>              Add a new task with description

        list                    List all task
            --status <status>   Filter by status
        
        delete <id>             Delete a task
        
        help                    Print help message

    TASK STATUS:
        in-progress             Task is in progress
        completed               Task is completed
    )";
    return;
}

std::vector<std::string> commandHandler::parse_args(int argc, char* argv[])
{
    std::vector<std::string> args;
    for (int i {2}; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    return args;
}

std::string commandHandler::get_option_value(const std::vector<std::string>& args, const std::string& option) const
{
    for (int i {0}; i < args.size(); ++i)
    {
        if (args[i] == option && i + 1 < args.size())
        {
            return args[++i];
        } 
    }
    return "";
}

bool commandHandler::has_option(const std::vector<std::string>& args, const std::string& option) const
{
    if (std::find(args.begin(), args.end(), option) != args.end())
    {
        return true;
    }
    return false;
}

commandHandler::commandHandler(const std::string& db_path){}

void commandHandler::execute(int argc, char *argv[])
{
    if (argc < 2)
    {
        handle_help();
        return;
    }
    std::string cmd = argv[1];
    std::vector<std::string> args = parse_args(argc, argv);

    if (cmd == "add") handle_add(args);
    else if (cmd == "delete") handle_delete(args);
    else if (cmd == "list") handle_list(args);
    else if (cmd == "update") handle_update(args);
    else if (cmd == "help") handle_help();
    else
    {
        std::cerr << "Unknown command\n";
        std::cout << "Run '" << argv[0] << " help' for usage\n";
    }
}