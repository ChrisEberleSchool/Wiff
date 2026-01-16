#include "./GrabCommand.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "argument/ParsedArgs.h"

/**
 *@ brief default constructor (does nothing here)
 * */
GrabCommand::GrabCommand() = default;

/**
 *@ brief returns the command namw (command is defined here)
 * */
std::string GrabCommand::name() const { return "grab"; }

/**
 *@ brief Main execution block that is called from main
 * */
void GrabCommand::execute(ApplicationContext &ctx) {
  // Ensure we are searching for something
  if (ctx.parsedArgs.targets.empty())
    throw std::invalid_argument(
        "Please enter a valid target you would like to search for!");

  // switch handling depending on type
  switch (ctx.parsedArgs.searchFlag) {
  case SearchBy::Extension:
    this->handleExtension(ctx);
    break;
  case SearchBy::FileName:
    this->handleFileName(ctx);
    break;
  case SearchBy::Stump:
    this->handleStump(ctx);
    break;
  default:
    throw std::logic_error("Unknown TypeFlag");
  }

  // Pretty explanatory what this is doing down here lol
  sortFoundFiles(ctx);

  // Program ends after execute so stop the loading animation
  ctx.threadManager.stopThread("loadingUI");

  // Draw At the end using one print statement cause speed
  printTableHeader();
  printFoundFiles();

  // Handle no file found case (Probaly move this elsewhere later on)
  if (this->foundFiles.empty()) {
    std::cout << "No Files Matching: " << ctx.parsedArgs.targets[0] << " In "
              << ctx.parsedArgs.dirPath << std::endl;
  }
}

/**
 *@ brief returns a description of the command.
          This is called by HelpCommannd for showing list.
 * */
std::string GrabCommand::description() const {
  return "Searches for files in bulk by name or extension. Defaults by full "
         "filename if no flag is provided. Defaults to searching current "
         "directory.";
}

/**
 *@ brief returns the usage of the command.
          This is called by HelpCommannd for showing list.
 * */
std::string GrabCommand::usage() const {
  return "wiff grab [search-flag] [target] [sort-flag] [directory]";
}

/**
 *@ brief Handles the recursive search for the extension
          flag case
 * */
void GrabCommand::handleExtension(ApplicationContext &ctx) {

  for (const auto &dir_entry : fs::recursive_directory_iterator{
           ctx.parsedArgs.dirPath,
           fs::directory_options::skip_permission_denied}) {
    if (!fs::is_regular_file(dir_entry.status()))
      continue;

    std::string ext = dir_entry.path().extension().string();
    if (!ext.empty() && ext[0] == '.')
      ext = ext.substr(1);

    if (ext != ctx.parsedArgs.targets[0])
      continue;

    foundFiles.push_back(FileEntry(dir_entry));
  }
}

/**
 *@ brief Handles the recursive search for the default
 * */
void GrabCommand::handleFileName(ApplicationContext &ctx) {
  for (const auto &dir_entry : fs::recursive_directory_iterator{
           ctx.parsedArgs.dirPath,
       }) {
    // skip non-files
    if (!fs::is_regular_file(dir_entry.status()))
      continue;

    // non matching file extensions skip
    if (dir_entry.path().filename().string() != ctx.parsedArgs.targets[0])
      continue;

    // add file to vector
    foundFiles.push_back(FileEntry(dir_entry));
  }
}

/**
 *@ brief Handles the recursive search for the name flag
          which just takes the files name not extension
 * */
void GrabCommand::handleStump(ApplicationContext &ctx) {
  for (const auto &dir_entry : fs::recursive_directory_iterator{
           ctx.parsedArgs.dirPath,
           fs::directory_options::skip_permission_denied}) {
    // skip non-files
    if (!fs::is_regular_file(dir_entry.status()))
      continue;

    // non matching file extensions skip
    if (dir_entry.path().stem().string() != ctx.parsedArgs.targets[0])
      continue;

    // add file to vector
    foundFiles.push_back(FileEntry(dir_entry));
  }
}

/**
 *@ brief Prints to console in one print statement
          the found files
 * */
std::string GrabCommand::printFoundFiles() {
  std::ostringstream out;
  for (const FileEntry &file : foundFiles) {
    out << std::left << std::setw(20) << file.path.filename().string()
        << std::setw(12) << formatSize(file.size) << std::setw(14)
        << formatDate(file.date_last_modified)
        << file.path.parent_path().string() << '\n';
  }
  return out.str();
}

/**
 *@ brief Sorts the found files depending on sortby flags given
 * */
void GrabCommand::sortFoundFiles(ApplicationContext &ctx) {
  switch (ctx.parsedArgs.sortFlag) {
  case SortBy::Alpha:
    std::sort(foundFiles.begin(), foundFiles.end(),
              [](const FileEntry &a, const FileEntry &b) {
                return a.filename < b.filename;
              });
    break;
  case SortBy::Date:
    std::sort(foundFiles.begin(), foundFiles.end(),
              [](const FileEntry &a, const FileEntry &b) {
                return a.date_last_modified > b.date_last_modified;
              });
    break;
  case SortBy::Size:
    std::sort(
        foundFiles.begin(), foundFiles.end(),
        [](const FileEntry &a, const FileEntry &b) { return a.size > b.size; });
    break;
  case SortBy::None:
    break;
  default:
    break;
  }
}
/**
 * @brief Prints to terminal the UI table for found files
 */
void GrabCommand::printTableHeader() {
  std::cout << std::left << std::setw(20) << "Filename" << std::setw(12)
            << "Size" << std::setw(14) << "Date"
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
std::string GrabCommand::formatDate(const fs::file_time_type &ftime) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(
      ftime - fs::file_time_type::clock::now() + system_clock::now());
  std::time_t cftime = system_clock::to_time_t(sctp);
  std::tm tm = *std::localtime(&cftime);
  std::ostringstream out;
  out << std::put_time(&tm, "%Y-%m-%d");
  return out.str();
}
