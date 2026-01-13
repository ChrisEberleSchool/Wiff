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

#include "command/base/Command.h"
#include "argument/ParsedArgs.h"

namespace fs = std::filesystem;

class HelpCommand : public Command {
public:
    HelpCommand( const std::unordered_map<std::string, std::unique_ptr<Command>>& commands);

    void execute(const ParsedArgs& args) override;
    
    std::string name() const override;
    std::string description() const override;
    std::string usage() const override;

private:
    const std::unordered_map<std::string, std::unique_ptr<Command>>& commands;

    void printOverview() const;
    void printCommand(const std::string& name) const;

    std::vector<const Command*> sortedCommands() const;
};
