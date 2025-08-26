#include "commandhandler.h"

void commandHandler::cli(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        std::printf("Argument %d: %s\n", i, argv[i]);
    }
}