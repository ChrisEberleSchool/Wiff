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

class GrabCommand : public Command {
public:
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
private:
    void handleExtension(const ArgumentParser& args, const std::string& dirPath) {
        // Table header
        printTableHeader();

        // recursive loop starting from provided directory
        for (const auto& dir_entry : fs::recursive_directory_iterator{dirPath}) {
            std::string extension = dir_entry.path().extension().string();
            
            // TODO:: Handle both include the . and not including the .
            if (extension == "." + args.target) {
                const auto& path = dir_entry.path();
                std::cout << std::left
                          << std::setw(20) << path.filename().string()
                          << std::setw(12) << formatSize(dir_entry.file_size())
                          << std::setw(14) << formatDate(dir_entry.last_write_time())
                          << path.parent_path().string()
                          << '\n';
            }
        }
    }

    void handleFileName(const ArgumentParser& args, const std::string& dirPath) {
        // Table header
        printTableHeader();
        
        // recursive loop starting from the provided directory
        for (const auto& dir_entry : fs::recursive_directory_iterator{dirPath, fs::directory_options::skip_permission_denied}) {
            if (!fs::is_regular_file(dir_entry.status()))
                continue;
        
            std::string file = dir_entry.path().stem().string();
            if (file == args.target) {
                const auto& path = dir_entry.path();
                std::cout << std::left
                          << std::setw(20) << path.filename().string()
                          << std::setw(12) << formatSize(dir_entry.file_size())
                          << std::setw(14) << formatDate(dir_entry.last_write_time())
                          << path.parent_path().string()
                          << '\n';
            }
        }
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
};
/*
    Example output:
        Filename             Size       Date        Path
        ------------------------------------------------------------
        hello.txt            0.1MB      2023-06-12  ./Documents
        world.log            2.3MB      2024-01-03  ./Logs
        project.cpp          12KB       2024-01-10  ~/Projects
*/