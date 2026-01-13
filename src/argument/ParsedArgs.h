#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/*
    SEARCH FLAGS:
        -e <extension>   # Find files by extension
        -n <filename>    # Find files by exact name

        --size           # Sort results by file size descending
        --date           # Sort results by date descending (newest first)
        --alpha          # Sort results alphabetically (default)
*/


const char FLAG_SPECIFIER = '-';
const char REL_DIR_SPECIFIER = '.';
const char ABS_DIR_SPECIFIER = '/';
const char HOME_DIR_SPECIFIER = '~';




/**
 * Defaults to FileName meaning looks for full file
 * path.
 *
 * */
enum struct SearchBy {
    FileName,
    Extension,
    Stump
};

/**
 * This enum struct will enforce singular
 * Sort flags. Current plan is to either throw
 * error if more than one is parsed or simply overwrite
 * previously parsed sort flag.
 *
 * */
enum struct SortBy {
    None,
    Size,
    Date,
    Alpha
}; 

struct ParsedArgs {
    std::string command;
    std::string dirPath;
    std::string target;
    SearchBy searchFlag;
    SortBy sortFlag;
    
    explicit ParsedArgs(int argc, char* argv[]);
  
    std::unordered_map<std::string, std::function<void()>> flagHandlers;
    void initFlagHandlers();

    void setFlags(const std::string& token);
    void setPositionals(const std::string& token);
};
