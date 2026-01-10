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

#include "./base/Command.h"
#include "../argument/ArgumentParser.h"

namespace fs = std::filesystem;

class HelpCommand : public Command {
public:
    HelpCommand( const std::unordered_map<std::string, std::unique_ptr<Command>>& commands) : commands(commands) {}

    std::string name() const override {
        return "help";
    }

    void execute(const ArgumentParser& args) override {

        if (args.target.empty()) {
            //iterate over commands in the mao
            printOverview();
        } else { // print the usage and desciption for the specified target
            printCommand(args.target);
        }

    }   

    std::string description() const override {
        return "Shows help information for commands";
    }

    std::string usage() const override {
        return "wiff help [command]";
    }

private:
     const std::unordered_map<std::string, std::unique_ptr<Command>>& commands;

    void printOverview() const {
        auto sorted = sortedCommands();

        std::cout << "Commands:\n\n";

        for (const auto* cmd : sorted) {
            std::cout << "  "
                      << std::left << std::setw(8) << cmd->name()
                      << cmd->description() << "\n"
                      << "  "
                      << std::setw(12) << ""
                      << "Usage:    " << cmd->usage()
                      << "\n\n";
        }

        std::cout << "Run 'wiff help <command>' for details.\n";
    }


    void printCommand(const std::string& name) const {
        auto it = commands.find(name);
        if (it == commands.end()) {
            throw std::runtime_error("Unknown command: " + name);
        }

        const Command& cmd = *it->second;

        std::cout << "Usage:\n"
                  << "  " << cmd.usage() << "\n\n"
                  << "Description:\n"
                  << "  " << cmd.description() << "\n";
    }

    std::vector<const Command*> sortedCommands() const {
        std::vector<const Command*> result;
        result.reserve(commands.size());

        for (const auto& [_, cmd] : commands) {
            result.push_back(cmd.get());
        }

        std::sort(result.begin(), result.end(),
                  [](const Command* a, const Command* b) {
                      return a->name() < b->name();
                  });

        return result;
    }
};
