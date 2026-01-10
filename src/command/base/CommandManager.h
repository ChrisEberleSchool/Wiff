#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

#include "./Command.h"
#include "../../argument/ArgumentParser.h"

/**
 * @brief Class that manages a unordered hashmap of
 *        Commands.
 */
class CommandManager {
public:
    CommandManager(int argc, char* argv[]) : argData(argc,argv) {}
    ~CommandManager () = default;

    void add(std::unique_ptr<Command> cmd) {
        // grab a copy of cmdName for quick access
        std::string cmdName = cmd->name();

        //check for duplicate command adding
        if(commandMap.contains(cmdName)) {
            throw std::logic_error("Duplicate command Registered: '"+cmdName);
        }
        commandMap[cmd->name()] = std::move(cmd);
    }

    void execute() {
        auto it = commandMap.find(argData.cmd);
        if (it == commandMap.end()) {
            throw std::runtime_error("Command not found: " + argData.cmd);
        }
        
        // call the commands execute with the argument data
        it->second->execute(argData);
    }
    
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commandMap;
    ArgumentParser argData;
};