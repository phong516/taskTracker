#include "commandhandler.h"


void commandHandler::handle_add(const std::vector<std::string>& args)
{
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
    return "";
}

bool commandHandler::has_option(const std::vector<std::string>& args, const std::string& option) const
{
    return false;
}

void commandHandler::execute(int argc, char *argv[])
{
    return;
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