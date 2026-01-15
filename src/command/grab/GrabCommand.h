#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "command/base/ICommand.h"
#include "context/ApplicationContext.h"

namespace fs = std::filesystem;

struct FileEntry {
  FileEntry(const fs::directory_entry &dir_entry)
      : path(dir_entry.path()), size(dir_entry.file_size()),
        date_last_modified(dir_entry.last_write_time()),
        filename(path.filename().string()) {}

  fs::path path;
  uintmax_t size;
  fs::file_time_type date_last_modified;
  std::string filename;
};

/**
 * @brief Finder tool.
 */
class GrabCommand : public ICommand {
public:
  std::vector<FileEntry> foundFiles;

  GrabCommand();

  void execute(ApplicationContext &ctx) override;

  std::string description() const override;
  std::string usage() const override;
  std::string name() const override;

private:
  void handleExtension(ApplicationContext &ctx);
  void handleFileName(ApplicationContext &ctx);
  void handleStump(ApplicationContext &ctx);

  void sortFoundFiles(ApplicationContext &ctx);
  /**
   * @brief creates the string representing the files size
   */
  std::string formatSize(uintmax_t bytes);

  /**
   * @brief Formats the date section
   */
  std::string formatDate(const fs::file_time_type &ftime);

  /**
   * @brief Prints to terminal the UI table for found files
   */
  void printTableHeader();
  void benchmarkPrintMethod();
  std::string printFoundFiles();
};
/*
    Example output:
        Filename             Size       Date        Path
        ------------------------------------------------------------
        hello.txt            0.1MB      2023-06-12  ./Documents
        world.log            2.3MB      2024-01-03  ./Logs
        project.cpp          12KB       2024-01-10  ~/Projects
*/
