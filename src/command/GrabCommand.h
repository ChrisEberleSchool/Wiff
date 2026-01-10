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

#include "./base/Command.h"
#include "../argument/ArgumentParser.h"

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

    GrabCommand() = default;

    std::string name() const override {
        return "grab";
    }

    void execute(const ArgumentParser& args) override {
        const std::string cwd = fs::current_path();

        // switch handling depending on type
        switch(args.typeFlag) {
            case TypeFlag::Extension:
                this->handleExtension(args, cwd);
                break;
            case TypeFlag::FileName:
                this->handleFileName(args, cwd);
                break;
            default:
                throw std::logic_error("Unknown TypeFlag");
        }
    }

    std::string description() const override {
        return "Searches for files in bulk by name or extension. Defaults by extension if no flag is provided.";
    }
    std::string usage() const override {
        return "wiff grab (-e <ext> | -n <name>) [--size|--date|--alpha]";
    }
private:
    void handleExtension(const ArgumentParser& args, const std::string& dirPath) {
        // recursive loop starting from provided directory
        for (const auto& dir_entry : fs::recursive_directory_iterator{dirPath, fs::directory_options::skip_permission_denied}) {
            // skip non-files
            if (!fs::is_regular_file(dir_entry.status()))
                continue;

            // ensure we can handle both <.ext> & <ext>
            std::string targetExt = args.target;
            if (!targetExt.empty() && targetExt[0] != '.')
                targetExt = "." + targetExt;

            // non matching file extensions skip
            if(dir_entry.path().extension().string() != targetExt) continue;
            
            // add file to vector
            foundFiles.push_back(FileEntry(dir_entry));
        }
        
        switch(args.filterFlag) {
            case FilterFlag::Alpha:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.filename < b.filename; });
                break;
            case FilterFlag::Date:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.date_last_modified > b.date_last_modified; });
                break;
            case FilterFlag::Size:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.size > b.size; });
                break;
            case FilterFlag::None:
                break;
            default:
                break;
        }

        benchmarkPrintMethod();
    }

    std::string printFoundFiles() {
        printTableHeader(); // optionally keep for console output

        std::ostringstream out;

        for (const FileEntry& file : foundFiles) {
            out << std::left
                << std::setw(20) << file.path.filename().string()
                << std::setw(12) << formatSize(file.size)
                << std::setw(14) << formatDate(file.date_last_modified)
                << file.path.parent_path().string()
                << '\n';
        }

        return out.str();
    }

    void handleFileName(const ArgumentParser& args, const std::string& dirPath) {
        // recursive loop starting from provided directory
        for (const auto& dir_entry : fs::recursive_directory_iterator{dirPath, fs::directory_options::skip_permission_denied}) {
            // skip non-files
            if (!fs::is_regular_file(dir_entry.status()))
                continue;

            
            // non matching file extensions skip
            if(dir_entry.path().stem().string() != args.target) continue;
            
            // add file to vector
            foundFiles.push_back(FileEntry(dir_entry));
        }
        
        switch(args.filterFlag) {
            case FilterFlag::Alpha:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.filename < b.filename; });
                break;
            case FilterFlag::Date:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.date_last_modified > b.date_last_modified; });
                break;
            case FilterFlag::Size:
                std::sort(foundFiles.begin(), foundFiles.end(),
                          [](const FileEntry& a, const FileEntry& b) { return a.size > b.size; });
                break;
            case FilterFlag::None:
                break;
            default:
                break;
        }

        benchmarkPrintMethod();
    }

    /**
     * @brief Prints to terminal the UI table for found files
     */
    void printTableHeader() {
        std::cout << std::left
                  << std::setw(20) << "Filename"
                  << std::setw(12) << "Size"
                  << std::setw(14) << "Date"
                  << "Path\n";
        std::cout << std::string(60, '-') << '\n';
    }

    /**
     * @brief creates the string representing the files size
     */
    std::string formatSize(uintmax_t bytes) {
        constexpr double KB = 1024.0;
        constexpr double MB = KB * 1024.0;

        std::ostringstream out;
        out << std::fixed << std::setprecision(1);

        if (bytes >= MB)
            out << (bytes / MB) << "MB";
        else
            out << (bytes / KB) << "KB";

        return out.str();
    }

    /**
     * @brief Formats the date section
     */
    std::string formatDate(const fs::file_time_type& ftime) {
        using namespace std::chrono;

        auto sctp = time_point_cast<system_clock::duration>(
            ftime - fs::file_time_type::clock::now()
            + system_clock::now()
        );

        std::time_t cftime = system_clock::to_time_t(sctp);
        std::tm tm = *std::localtime(&cftime);

        std::ostringstream out;
        out << std::put_time(&tm, "%Y-%m-%d");
        return out.str();
    }

    #include <chrono>

    void benchmarkPrintMethod() {

        // Method 1: ostringstream
        auto start1 = std::chrono::high_resolution_clock::now();
        std::string result1 = printFoundFiles();
        std::cout << result1;
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = duration_cast<std::chrono::microseconds>(end1 - start1).count();
        std::cout << "printFoundFiles1() took: " << duration1 << " µs\n";
    }

};
/*
    Example output:
        Filename             Size       Date        Path
        ------------------------------------------------------------
        hello.txt            0.1MB      2023-06-12  ./Documents
        world.log            2.3MB      2024-01-03  ./Logs
        project.cpp          12KB       2024-01-10  ~/Projects
*/