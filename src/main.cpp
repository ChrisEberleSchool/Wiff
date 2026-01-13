#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

#include "command/base/Command.h"
#include "command/manager/CommandManager.h"

#include "command/grab/GrabCommand.h"
#include "command/help/HelpCommand.h"
#include "argument/ParsedArgs.h"
#include "ui/loading/LoadingUI.h"


int main(int argc, char* argv[]) {
    try {
        // Loading anim thread
        LoadingUI loadingThread;
        ParsedArgs args(argc,argv);

        //create the managers and arguments class
        CommandManager cmdManager;

        // populate the command manager
        cmdManager.add(std::make_unique<GrabCommand>());
        cmdManager.add(std::make_unique<HelpCommand>(cmdManager.commands()));
        cmdManager.execute(args);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
	
    return 0;
}
