#include "./CommandManager.h"


CommandManager::CommandManager() {}

void CommandManager::add(std::unique_ptr<ICommand> cmd) {
    // grab a copy of cmdName for quick access
    std::string cmdName = cmd->name();
    //check for duplicate command adding
    if(commandMap.contains(cmdName)) {
        throw std::logic_error("Duplicate command Registered: '"+cmdName);
    }
    commandMap[cmd->name()] = std::move(cmd);
}

void CommandManager::execute(ApplicationContext& ctx) {
    auto it = commandMap.find(ctx.parsedArgs.command);
    if (it == commandMap.end()) {
        throw std::runtime_error("Command not found. Try: wiff help" + ctx.parsedArgs.command);
    }
    // call the commands execute with the argument data
    it->second->execute(ctx);
}

const std::unordered_map<std::string, std::unique_ptr<ICommand>>& CommandManager::commands() const {
    return commandMap;
}
