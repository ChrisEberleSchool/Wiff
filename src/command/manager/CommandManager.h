#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "context/ApplicationContext.h"

#include "command/base/ICommand.h"

/**
 * @brief Class that manages a unordered hashmap of
 *        Commands.
 */
class CommandManager {
public:
  CommandManager();
  ~CommandManager() = default;

  void execute(ApplicationContext &ctx);

  const std::unordered_map<std::string, std::unique_ptr<ICommand>> &
  commands() const;

private:
  std::unordered_map<std::string, std::unique_ptr<ICommand>> commandMap;
  void add(std::unique_ptr<ICommand> cmd);
};
