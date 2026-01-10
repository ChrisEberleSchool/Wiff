#include "./CommandManager.h"


CommandManager::CommandManager(int argc, char* argv[])
    : argData(argc, argv) {}

void CommandManager::add(std::unique_ptr<Command> cmd) {
    // grab a copy of cmdName for quick access
    std::string cmdName = cmd->name();
    //check for duplicate command adding
    if(commandMap.contains(cmdName)) {
        throw std::logic_error("Duplicate command Registered: '"+cmdName);
    }
    commandMap[cmd->name()] = std::move(cmd);
}

void CommandManager::execute() {
    auto it = commandMap.find(argData.cmd);
    if (it == commandMap.end()) {
        throw std::runtime_error("Command not found. Try: wiff help" + argData.cmd);
    }
    // call the commands execute with the argument data
    it->second->execute(argData);
}

const std::unordered_map<std::string, std::unique_ptr<Command>>& CommandManager::commands() const {
    return commandMap;
}