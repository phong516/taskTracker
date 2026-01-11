#include "model/taskmanager.h"
#include "view/taskview.h"
#include "controller/commandhandler.h"
#include "storage/jsonstorage.h"

int main(int argc, char *argv[])
{
	commandHandler controller {};
	controller.execute(argc, argv);	
	return 0;
}
