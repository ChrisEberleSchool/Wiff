#pragma once

#include <argument/ParsedArgs.h>
#include <threads/manager/ThreadManager.h>

struct ApplicationContext
{
    ApplicationContext(int argc, char *argv[])
        : parsedArgs(argc, argv) {}

    ThreadManager threadManager;
    ParsedArgs parsedArgs;
};
