#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "./command/base/Command.h"
#include "./command/base/CommandManager.h"

#include "./command/GrabCommand.h"
#include "./argument/Arguments.h"


int main(int argc, char* argv[]) {

    //create the managers and arguments class
    Arguments arguments(argc, argv);
    CommandManager cmdManager(arguments);

    // populate the command manager
    cmdManager.add(std::make_unique<GrabCommand>());

    Command& cmd = cmdManager.getRef();
    cmd.execute(arguments);

    return 0;
}