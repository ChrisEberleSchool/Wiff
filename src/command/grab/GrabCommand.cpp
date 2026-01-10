#include "./GrabCommand.h"


GrabCommand::GrabCommand() = default;
std::string GrabCommand::name() const { return "grab"; }
void GrabCommand::execute(const ArgumentParser& args) {
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

std::string GrabCommand::description() const {
    return "Searches for files in bulk by name or extension. Defaults by extension if no flag is provided.";
}

std::string GrabCommand::usage() const {
    return "wiff grab (-e <ext> | -n <name>) [--size|--date|--alpha]";
}

void GrabCommand::handleExtension(const ArgumentParser& args, const std::string& dirPath) {
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

std::string GrabCommand::printFoundFiles() {
    printTableHeader(); 
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

void GrabCommand::handleFileName(const ArgumentParser& args, const std::string& dirPath) {
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
void GrabCommand::printTableHeader() {
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
std::string GrabCommand::formatSize(uintmax_t bytes) {
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
std::string GrabCommand::formatDate(const fs::file_time_type& ftime) {
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

void GrabCommand::benchmarkPrintMethod() {
    // Method 1: ostringstream
    auto start1 = std::chrono::high_resolution_clock::now();
    std::string result1 = printFoundFiles();
    std::cout << result1;
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::microseconds>(end1 - start1).count();
    std::cout << "printFoundFiles1() took: " << duration1 << " µs\n";
}