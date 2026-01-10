#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

#include "./Command.h"
#include "../../argument/Arguments.h"

/**
 * @brief Class that manages a unordered hashmap of
 *        Commands.
 */
class CommandManager {
public:
    CommandManager(Arguments& arguments) : arguments(arguments) {}
    ~CommandManager () = default;

    void add(std::unique_ptr<Command> cmd) {
        commandMap[cmd->getCmdName()] = std::move(cmd);
    }

    // Grabs a reference to the command the user inputted
    Command& getRef() {
        auto it = commandMap.find(arguments.cmd);
        if (it == commandMap.end()) {
            throw std::runtime_error("Command not found: " + arguments.cmd);
        }
        return *(it->second);
    }
    
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commandMap;
    Arguments& arguments;
};