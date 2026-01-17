#include "command/git/GitCommand.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "argument/ParsedArgs.h"
#include "util/StringUtils.h"

GitCommand::GitCommand() {
  // cross platform dirs to skip
  skipDirs = {"node_modules",
              ".cache",
              ".npm",
              "dist",
              "build",
              "bin",
              "obj",
              "out",
#if defined(_WIN32) || defined(_WIN64)
              "Recycle Bin",
              "$RECYCLE.BIN",
              "AppData",
              "Program Files",
              "Program Files (x86)",
              "ProgramData",
              "Windows",
              "Temp",
#endif
#if defined(__APPLE__)
              ".Trash",
              "Library",
              "Applications",
              "System",
              "Volumes",
              "Pictures"
#endif
#if defined(__linux__)
              "Trash",
              ".local",
              "Downloads",
              "snap",
              "lib",
              "var",
              "bin",
              "sbin",
              "usr",
              "opt",
              "tmp",
              "mnt",
              "Pictures"

#endif
  };
}

void GitCommand::execute(ApplicationContext &ctx) {
  // init here prevents continous reint in recursive loop
  fs::path currDir;

  fs::path homeDir =

  // grab the directory path depending on the users operating system
#if defined(_WIN32) || defined(_WIN64)
      std::getenv("USERPROFILE");
#elif defined(__APPLE__) || defined(__linux__)
      std::getenv("HOME");
#else
#error "Unsupported OS"
#endif

  auto start = std::chrono::steady_clock::now();

  // takes the project name we are searching for and sets
  // it to lower case so we still find projects regardless
  // off capitlization.
  std::string targetLower = toLower(ctx.parsedArgs.targets[0]);

  // commondevdirs is the list of common dirs youd most find github projects in
  std::vector<std::string> commonDevDirs{"dev", "documents", "projects",
                                         "github", "code"};
  bool foundEarly = false;

  for (const auto &d : commonDevDirs) {
    fs::path p = homeDir / d;
    if (fs::exists(p) && fs::is_directory(p)) {
      // first recurse into it
      if (this->recurseDir(p, targetLower)) {
        // if found make sure we set foundEarly true
        foundEarly = true;
        break;
      } else {
        // wasnt found so add to the set of avoid dirs
        skipDirs.insert(d);
      }
    }
  }
  // only recurse from home dir if not found early
  if (!foundEarly) {
    this->recurseDir(homeDir, targetLower);
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::milli> duration_double_ms = end - start;
  std::cout << "Execution time: " << duration_double_ms.count() << " ms"
            << std::endl;

  // stop the loading thread
  ctx.threadManager.stopThread("loadingUI");

  if (foundDirs.empty()) {
    std::cout << "No Git projects found." << std::endl;
    return;
  }

  fs::path projectPath = fs::absolute(foundDirs[0]);
  std::cout << "Found project at: " << projectPath << std::endl;

  // Determine which program to open with
  // init with 'code' as default if non second target
  std::string opener = "code";
  if (ctx.parsedArgs.targets.size() >= 2) {
    opener = ctx.parsedArgs.targets[1];
  }

  // Build command
  std::string userCommand;

  // Depending on OS and target opener create the sys command
  if (opener == "code" || opener == "vs") {
    userCommand = "code \"" + projectPath.string() + "\"";
  } else if (isCliEditor(opener)) {
#if defined(_WIN32) || defined(_WIN64)
    userCommand =
        "cmd /C \"cd /D \"" + projectPath.string() + "\" && " + opener + "\"";
#else
    userCommand =
        "sh -c \"cd '" + projectPath.string() + "' && " + opener + " .\"";
#endif
  } else if (opener == "default") {
#if defined(__APPLE__)
    userCommand = "open \"" + projectPath.string() + "\"";
#elif defined(__linux__)
    userCommand = "xdg-open \"" + projectPath.string() + "\"";
#elif defined(_WIN32) || defined(_WIN64)
    userCommand = "explorer \"" + projectPath.string() + "\"";
#endif
  } else {
    // Unknown program: assume GUI-style invocation
    userCommand = opener + " \"" + projectPath.string() + "\"";
  }

  std::cout << "Running: " << userCommand << std::endl;
  int ret = std::system(userCommand.c_str());
  if (ret != 0)
    std::cerr << "Command failed with exit code: " << ret << std::endl;
}

std::string GitCommand::description() const {
  return "Opens github projects given the project name. Defaults to vs code if "
         "no program to open with target is defined";
}

std::string GitCommand::usage() const {
  return "wiff git [project-name] <or if u want to open with something else> "
         "wiff git [project-name] "
         "[program-to-open-with]";
}

std::string GitCommand::name() const { return "git"; }

bool GitCommand::isCliEditor(const std::string &opener) {
  static const std::unordered_set<std::string> cliEditors = {
      "nvim", "vim",   "vi",    "nano", "emacs", "emacsclient",
      "hx",   "helix", "micro", "kak",  "less"};
  return cliEditors.contains(opener);
}

bool GitCommand::recurseDir(const fs::path &root,
                            const std::string &targetLower) {
  for (auto it = fs::recursive_directory_iterator(
           root, fs::directory_options::skip_permission_denied);
       it != fs::recursive_directory_iterator(); ++it) {

    if (!it->is_directory())
      continue;

    const std::string dirName = it->path().filename().string();

    if (skipDirs.contains(dirName)) {
      it.disable_recursion_pending();
      continue;
    }

    if (toLower(dirName) != targetLower)
      continue;

    if (!fs::is_directory(it->path() / ".git"))
      continue;

    foundDirs.push_back(it->path());
    return true;
  }

  return false;
}
