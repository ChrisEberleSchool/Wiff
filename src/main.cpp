#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

#include "command/base/ICommand.h"
#include "command/manager/CommandManager.h"

#include "command/grab/GrabCommand.h"
#include "command/help/HelpCommand.h"
#include "argument/ParsedArgs.h"
#include "threads/manager/ThreadManager.h"
#include "threads/loading/LoadingThread.h"
#include "context/ApplicationContext.h"

int main(int argc, char *argv[])
{
    try
    {
        ApplicationContext appCtx(argc, argv);
        appCtx.threadManager.add("loadingUI", std::make_unique<LoadingThread>());

        appCtx.threadManager.startThread("loadingUI");

        // create the managers and arguments class
        CommandManager cmdManager;

        // populate the command manager
        cmdManager.add(std::make_unique<GrabCommand>());
        cmdManager.add(std::make_unique<HelpCommand>(cmdManager.commands()));
        cmdManager.execute(appCtx);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
