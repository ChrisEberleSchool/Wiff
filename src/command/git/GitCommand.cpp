#include "command/git/GitCommand.h"

#include <cstdlib>
#include <iostream>

#include "argument/ParsedArgs.h"

GitCommand::GitCommand() {}

void GitCommand::execute(ApplicationContext &ctx) {
  // once found look for .git dir in it
  // enter shell command
  // wiff git name with
  // Search from home directory for dir that == target
  std::string currFile;

  std::string dirPath = fs::current_path();
  dirPath = "~";

  for (const auto &dir_entry : fs::recursive_directory_iterator{
           dirPath, fs::directory_options::skip_permission_denied}) {

    currFile = dir_entry.path().filename().string();
    // if not a dir skip
    if (!dir_entry.is_directory())
      continue;
    // non matching file extensions skip
    if (currFile != ctx.parsedArgs.targets[0])
      continue;

    // check for .git
    if (!this->isGit(dir_entry.path().relative_path()))
      continue;

    foundDirs.push_back(dir_entry.path());
  }

  // For now just direct to first foundDir
  if (foundDirs.empty()) {
    std::cout << "No Git projects found." << std::endl;
  } else {
    // navigate to projcet root using target[1]
    std::string command = "cd ";
    command += foundDirs[0].filename().string();
    std::cout << "COMMAND -> " << command << std::endl;
    // std::system(command);
  }
}

std::string GitCommand::description() const {
  return "Opens github projects given the project name and program to open "
         "with";
}

std::string GitCommand::usage() const {
  return "wiff git [project-name] [program-to-open-with]";
}

std::string GitCommand::name() const { return "git"; }

bool GitCommand::isGit(const fs::path &path) {
  // search current dir for.git
  std::ranges::for_each(std::filesystem::directory_iterator{path},
                        [](const auto &dir_entry) {
                          if (dir_entry.path().filename().string() == ".git")
                            return true;
                          return false;
                        });

  return false;
}
