#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

enum struct TypeFlag {
   Extension,
   FileName
};

enum struct FilterFlag {
    None,
    Size,
    Date,
    Alpha
};

/*
    SEARCH FLAGS:
        -e <extension>   # Find files by extension
        -n <filename>    # Find files by exact name

    FILTER FLAGS:
        --size           # Sort results by file size descending
        --date           # Sort results by date descending (newest first)
        --alpha          # Sort results alphabetically (default)
*/
struct Arguments {
public:
    Arguments(int argc, char* argv[]) : filterFlag(FilterFlag::None), typeFlag(TypeFlag::Extension) {

        // invalid args case
        if (argc < 3) {
            throw std::runtime_error("Invalid Command: To see commands type  -> wiff help \n");
        }

        // Grab the command
        cmd = argv[1];

        // initialize the command map
        commands = {
            { "-e", [this]() { typeFlag = TypeFlag::Extension; } },
            { "-n", [this]() { typeFlag = TypeFlag::FileName; } },

            { "--size", [this]() { filterFlag = FilterFlag::Size; } },
            { "--date", [this]() { filterFlag = FilterFlag::Date; } },
            { "--alpha", [this]() { filterFlag = FilterFlag::Alpha; } }
        };
        
        // iterates through  arguments to find flags and targetData
        for(int i = 2; i < argc; i++) {
            std::string arg = argv[i];

            auto it = commands.find(arg);
            if(it != commands.end()) {
                it->second();
            } else {
                // if target data has already been produced skip
                if(!targetDefined) {
                    target = arg;
                    targetDefined = true;
                }
            }
        }

        // in the case where no target data was inputted throw a runtime error.
        if (target.empty()) {
            throw std::runtime_error("Invalid Command: To see commands type  -> wiff help \n");
        }
    }

    std::string cmd;
    TypeFlag typeFlag;
    FilterFlag filterFlag;
    std::string target;
private:
    using func = std::function<void()>;
    std::unordered_map<std::string, func> commands;
    bool targetDefined = false;
};