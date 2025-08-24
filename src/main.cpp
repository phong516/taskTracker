#include "taskmanager.h"
#include "taskview.h"
#include "commandhandler.h"
#include "json.h"

int main(int argc, char * argv[])
{
	std::printf("Task Tracker!!!\n");
	taskView view;
	taskManager model;
	commandHandler controller(model, view);
	controller.cli(argc, argv);
	std::ifstream file{"task.json"};
	if (!file)
	{
		std::cout << "File error\n";
		return 1;
	}
	std::string strInput{};
	while (file >> strInput)
	{
	std::cout << strInput;
	}

	return 0;
}

