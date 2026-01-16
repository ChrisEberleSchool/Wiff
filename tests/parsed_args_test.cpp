#include "argument/ParsedArgs.h"
#include <gtest/gtest.h>

#include <filesystem>
namespace fs = std::filesystem;

/**
 * @brief Tests that the command is parsed correctly from argv.
 */
TEST(ParsedArgsTests, ParsesCommandCorrectly) {
  char *argv[] = {(char *)"wiff", (char *)"grab"};
  int argc = 2;

  ParsedArgs args(argc, argv);
  EXPECT_EQ(args.command, "grab");
}

/**
 * @brief Tests that the -e search flag sets SearchBy::Extension
 *        and captures the target correctly.
 */
TEST(ParsedArgsTests, ParsesSearchFlags) {
  char *argv[] = {(char *)"wiff", (char *)"grab", (char *)"-e", (char *)"txt"};
  int argc = 4;

  ParsedArgs args(argc, argv);
  EXPECT_EQ(args.searchFlag, SearchBy::Extension);
  EXPECT_EQ(args.targets[0], "txt");
}

/**
 * @brief Tests that sort flags like --size are parsed and set correctly.
 */
TEST(ParsedArgsTests, ParsesSortFlags) {
  char *argv[] = {(char *)"wiff", (char *)"grab", (char *)"--size"};
  int argc = 3;

  ParsedArgs args(argc, argv);
  EXPECT_EQ(args.sortFlag, SortBy::Size);
}

/**
 * @brief Tests that positional arguments are correctly assigned
 *        to target and directory path.
 */
TEST(ParsedArgsTests, ParsesDirectoryAndTarget) {
  std::string dir = "/tmp/testdir";
  char *argv[] = {(char *)"wiff", (char *)"grab", (char *)"myfile.txt",
                  (char *)dir.c_str()};
  int argc = 4;

  ParsedArgs args(argc, argv);
  EXPECT_EQ(args.targets[0], "myfile.txt");
  EXPECT_EQ(args.dirPath, dir);
}

/**
 * @brief Tests that an invalid flag throws a runtime_error.
 */
TEST(ParsedArgsTests, ThrowsOnInvalidFlag) {
  char *argv[] = {(char *)"wiff", (char *)"grab", (char *)"--notreal"};
  int argc = 3;

  EXPECT_THROW({ ParsedArgs args(argc, argv); }, std::runtime_error);
}

/**
 * @brief Tests that defaults are correctly applied when no flags
 *        or directory/target arguments are provided.
 */
TEST(ParsedArgsTests, DefaultsDirPathAndFlags) {
  char *argv[] = {(char *)"wiff", (char *)"grab"};
  int argc = 2;

  ParsedArgs args(argc, argv);
  EXPECT_EQ(args.searchFlag, SearchBy::FileName);
  EXPECT_EQ(args.sortFlag, SortBy::None);
  EXPECT_EQ(args.dirPath, fs::current_path());
}
