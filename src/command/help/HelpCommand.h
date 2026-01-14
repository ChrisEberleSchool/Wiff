#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "command/base/ICommand.h"
#include "context/ApplicationContext.h"

namespace fs = std::filesystem;

class HelpCommand : public ICommand {
public:
    HelpCommand( const std::unordered_map<std::string, std::unique_ptr<ICommand>>& commands);

    void execute(ApplicationContext& ctx) override;
    
    std::string name() const override;
    std::string description() const override;
    std::string usage() const override;

private:
    const std::unordered_map<std::string, std::unique_ptr<ICommand>>& commands;

    void printOverview() const;
    void printCommand(const std::string& name) const;

    std::vector<const ICommand*> sortedCommands() const;
};
