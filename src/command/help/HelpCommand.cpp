#include "./HelpCommand.h"



HelpCommand::HelpCommand( const std::unordered_map<std::string, std::unique_ptr<Command>>& commands) : commands(commands) {}

std::string HelpCommand::name() const {
    return "help";
}

void HelpCommand::execute(const ArgumentParser& args) {
    if (args.target.empty()) {
        //iterate over commands in the mao
        printOverview();
    } else { // print the usage and desciption for the specified target
        printCommand(args.target);
    }
}

std::string HelpCommand::description() const {
    return "Shows help information for commands";
}

std::string HelpCommand::usage() const {
    return "wiff help [command]";
}

void HelpCommand::printOverview() const {
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

void HelpCommand::printCommand(const std::string& name) const {
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

std::vector<const Command*> HelpCommand::sortedCommands() const {
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