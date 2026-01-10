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
struct ArgumentParser {
public:
    ArgumentParser(int argc, char* argv[]) : filterFlag(FilterFlag::None), typeFlag(TypeFlag::Extension) {

        // invalid args case
        if (argc < 2) {
            throw std::runtime_error("No command provided. Try: wiff help");
        }

        cmd = argv[1];

        // initialize the command map
        flagHandlers = {
            { "-e", [this]() { typeFlag = TypeFlag::Extension; } },
            { "-n", [this]() { typeFlag = TypeFlag::FileName; } },

            { "--size", [this]() { filterFlag = FilterFlag::Size; } },
            { "--date", [this]() { filterFlag = FilterFlag::Date; } },
            { "--alpha", [this]() { filterFlag = FilterFlag::Alpha; } }
        };
        
        // iterates through  arguments to find flags and targetData
        for(int i = 2; i < argc; i++) {
            std::string arg = argv[i];

            auto it = flagHandlers.find(arg);
            if(it != flagHandlers.end()) {
                it->second();
            } else {
                // if target data has already been produced skip
                if(!targetDefined) {
                    target = arg;
                    targetDefined = true;
                }
            }
        }
    }

    std::string cmd;
    TypeFlag typeFlag;
    FilterFlag filterFlag;
    std::string target;
private:
    using func = std::function<void()>;
    std::unordered_map<std::string, func> flagHandlers;
    bool targetDefined = false;
};