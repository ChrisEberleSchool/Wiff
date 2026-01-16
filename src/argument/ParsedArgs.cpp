#include "ParsedArgs.h"

#include <filesystem>
#include <stdexcept>
namespace fs = std::filesystem;

ParsedArgs::ParsedArgs(int argc, char *argv[]) {
  if (argc < 2) {
    throw std::runtime_error("No command provided. Try: wiff help");
  }
  // Default the flags and dirPath
  sortFlag = SortBy::None;
  searchFlag = SearchBy::FileName;

  // default the dirPath to the current directory
  dirPath = fs::current_path().string();

  initFlagHandlers();

  // this sets the command arg
  command = argv[1];

  for (int i = 2; i < argc; ++i) {
    std::string token = argv[i];

    if (token.empty())
      continue;

    if (token[0] == FLAG_SPECIFIER) {
      setFlags(token);
    } else {
      // Decipher whether or not it is a path
      // to a file we want or if it is a path
      // to what dir we want
      setPositionals(token);
    }
  }
}

void ParsedArgs::initFlagHandlers() {
  // Initialize the flag handlers
  this->flagHandlers = {{"-e", [this]() { searchFlag = SearchBy::Extension; }},
                        {"-n", [this]() { searchFlag = SearchBy::Stump; }},

                        {"--size", [this]() { sortFlag = SortBy::Size; }},
                        {"--date", [this]() { sortFlag = SortBy::Date; }},
                        {"--alpha", [this]() { sortFlag = SortBy::Alpha; }}};
}

void ParsedArgs::setFlags(const std::string &token) {
  // If the flag exists add the specified flag to vec
  auto it = flagHandlers.find(token);
  if (it != flagHandlers.end()) {
    it->second();
  }
  // throw flag notexist runtime_error
  else {
    throw std::runtime_error("Flag: " + token +
                             " does not exist. Try wiff help");
  }
}

void ParsedArgs::setPositionals(const std::string &token) {
  // Already defaulted in constructor so we return
  if (token[0] == REL_DIR_SPECIFIER)
    return;

  // Set to specified path
  if (token[0] == ABS_DIR_SPECIFIER || token[0] == HOME_DIR_SPECIFIER) {
    dirPath = token;
    return;
  }
  targets.push_back(token);
}
