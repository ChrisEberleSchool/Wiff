#include "./CommandManager.h"

#include <iostream>
#include <stdexcept>

#include "command/grab/GrabCommand.h"
#include "command/help/HelpCommand.h"

CommandManager::CommandManager() {
  // populate the command manager
  this->add(std::make_unique<GrabCommand>());
  this->add(std::make_unique<HelpCommand>(this->commands()));
}

void CommandManager::add(std::unique_ptr<ICommand> cmd) {
  // grab a copy of cmdName for quick access
  std::string cmdName = cmd->name();
  // check for duplicate command adding
  if (commandMap.contains(cmdName)) {
    throw std::logic_error("Duplicate command Registered: '" + cmdName);
  }
  commandMap[cmd->name()] = std::move(cmd);
}

void CommandManager::execute(ApplicationContext &ctx) {
  auto it = commandMap.find(ctx.parsedArgs.command);
  if (it == commandMap.end()) {
    throw std::runtime_error("Command not found. Try: wiff help" +
                             ctx.parsedArgs.command);
  }
  // call the commands execute with the argument data
  it->second->execute(ctx);
}

const std::unordered_map<std::string, std::unique_ptr<ICommand>> &
CommandManager::commands() const {
  return commandMap;
}
