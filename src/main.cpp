#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "./command/base/Command.h"
#include "./command/base/CommandManager.h"

#include "./command/GrabCommand.h"
#include "./command/HelpCommand.h"
#include "./argument/ArgumentParser.h"


int main(int argc, char* argv[]) {
    try {
        //create the managers and arguments class
        CommandManager cmdManager(argc, argv);

        // populate the command manager
        cmdManager.add(std::make_unique<GrabCommand>());
        cmdManager.add(std::make_unique<HelpCommand>(cmdManager.commands()));

        cmdManager.execute();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }


    return 0;
}