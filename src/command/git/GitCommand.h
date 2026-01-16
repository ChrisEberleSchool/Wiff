#pragma once

#include "command/base/ICommand.h"
#include "context/ApplicationContext.h"
#include <filesystem>
#include <string>
#include <unordered_set>

namespace fs = std::filesystem;

class GitCommand : public ICommand {
public:
  std::vector<fs::path> foundDirs;

  GitCommand();

  void execute(ApplicationContext &ctx) override;

  std::string description() const override;
  std::string usage() const override;
  std::string name() const override;

private:
  bool isGit(const fs::path &path);

  std::unordered_set<std::string> skipDirs;
};
