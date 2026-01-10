#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "command/base/Command.h"
#include "argument/ArgumentParser.h"

namespace fs = std::filesystem;

struct FileEntry {
    FileEntry(const fs::directory_entry& dir_entry)
        : path(dir_entry.path()), size(dir_entry.file_size()),
          date_last_modified(dir_entry.last_write_time()),
          filename(path.filename().string()) {}

    fs::path path;
    uintmax_t size;
    fs::file_time_type date_last_modified;
    std::string filename;
};


class GrabCommand : public Command {
public:
    std::vector<FileEntry> foundFiles;

    GrabCommand();

    void execute(const ArgumentParser& args) override;

    std::string description() const override;
    std::string usage() const override;
    std::string name() const override;
private:
    void handleExtension(const ArgumentParser& args, const std::string& dirPath);
    void handleFileName(const ArgumentParser& args, const std::string& dirPath);

    /**
     * @brief creates the string representing the files size
     */
    std::string formatSize(uintmax_t bytes);

    /**
     * @brief Formats the date section
     */
    std::string formatDate(const fs::file_time_type& ftime);

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