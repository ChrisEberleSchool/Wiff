#include <gtest/gtest.h>

#include "command/base/ICommand.h"
#include "command/grab/GrabCommand.h"

TEST(CommandTests, GrabInitializes) {
    std::unique_ptr<ICommand> cmd = std::make_unique<GrabCommand>();
    EXPECT_NE(cmd, nullptr);
}