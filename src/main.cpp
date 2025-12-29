#include "model/taskmanager.h"
#include "view/taskview.h"
#include "controller/commandhandler.h"
//#include "json.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main(int argc, char *argv[])
{
	std::printf("Task Tracker!!!\n");
	taskView view{};
	taskManager model{};
	commandHandler controller(model, view);
	controller.cli(argc, argv);
	json a {};
	return 0;
}
