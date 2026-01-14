#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

#include "command/base/ICommand.h"
#include "argument/ParsedArgs.h"
#include "context/ApplicationContext.h"


/**
 * @brief Class that manages a unordered hashmap of
 *        Commands.
 */
class CommandManager {
public:
    CommandManager();
    ~CommandManager () = default;

    void add(std::unique_ptr<ICommand> cmd);

    void execute(ApplicationContext& ctx);

    const std::unordered_map<std::string, std::unique_ptr<ICommand>>& commands() const;
    
private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commandMap;
};
