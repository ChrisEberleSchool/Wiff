#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

#include "command/base/Command.h"
#include "argument/ParsedArgs.h"


/**
 * @brief Class that manages a unordered hashmap of
 *        Commands.
 */
class CommandManager {
public:
    CommandManager();
    ~CommandManager () = default;

    void add(std::unique_ptr<Command> cmd);

    void execute(const ParsedArgs& args);

    const std::unordered_map<std::string, std::unique_ptr<Command>>& commands() const;
    
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commandMap;
};
