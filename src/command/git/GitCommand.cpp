#include "command/git/GitCommand.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "argument/ParsedArgs.h"

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
              "Desktop",
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

  fs::path target{ctx.parsedArgs.targets[0]};

  // Iterate through directory starting from system home to find target dir
  for (auto i = fs::recursive_directory_iterator(homeDir);
       i != fs::recursive_directory_iterator(); i++) {

    // if not a dir skip
    if (!i->is_directory())
      continue;

    // set the current file string
    currDir = i->path().filename();

    // SKIP DIRECTORIES opted out of
    if (this->skipDirs.contains(currDir.string())) {
      i.disable_recursion_pending();
      continue;
    }

    // non matching file extensions skip
    if (currDir != target)
      continue;

    // Git projects must have .git folder in root dir to be recognized
    if (!fs::is_directory(i->path() / ".git"))
      continue;

    foundDirs.push_back(i->path());
    break;
  }
  // stop the loading thread
  ctx.threadManager.stopThread("loadingUI");

  if (foundDirs.empty()) {
    std::cout << "No Git projects found." << std::endl;
    return;
  }

  // Change to the project folder (foundDirs[0] is the path)
  fs::current_path(foundDirs[0]);
  std::cout << "Opening project at: " << foundDirs[0] << std::endl;

  // Check if user specified a program to open with
  if (ctx.parsedArgs.targets.size() < 2) {
    std::cout << "No program specified to open with." << std::endl;
    return;
  }

  // Build command using targets[1..n]
  std::string userCommand;
  for (size_t i = 1; i < ctx.parsedArgs.targets.size(); ++i) {
    userCommand += ctx.parsedArgs.targets[i] + " ";
  }

  std::cout << "Running: " << userCommand << std::endl;

  // Run the user’s command in the project folder
  int ret = std::system(userCommand.c_str());
  if (ret != 0)
    std::cerr << "Command failed with exit code: " << ret << std::endl;

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::milli> duration_double_ms = end - start;
  std::cout << "Execution time (double): " << duration_double_ms.count()
            << " ms" << std::endl;
}

std::string GitCommand::description() const {
  return "Opens github projects given the project name and program to open "
         "with";
}

std::string GitCommand::usage() const {
  return "wiff git [project-name] [program-to-open-with]";
}

std::string GitCommand::name() const { return "git"; }
