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
    ArgumentParser(int argc, char* argv[]);
    
    std::string cmd;
    TypeFlag typeFlag;
    FilterFlag filterFlag;
    std::string target;
private:
    using func = std::function<void()>;
    std::unordered_map<std::string, func> flagHandlers;
    bool targetDefined = false;
};