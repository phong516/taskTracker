#include "model/taskmanager.h"
#include "view/taskview.h"
#include "controller/commandhandler.h"
#include "storage/jsonstorage.h"
using json = nlohmann::json;

int main(int argc, char *argv[])
{
	std::printf("Task Tracker!!!\n");
	taskView view{};
	taskManager model{};
	commandHandler controller(model, view);
	controller.cli(argc, argv);
	storage db;
	db.init();
	db.add("clean the house");
	db.update("1", "desc", "remove the trash bin");
	db.update("2", "status", "done");
	db.remove("3");
	for (auto task: db.list())
	{
		std::cout << task.dump(DEFAULT_INDENT);
	}
	db.save();
	return 0;
}
