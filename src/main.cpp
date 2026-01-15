#include <iostream>
#include <string>

#include "command/manager/CommandManager.h"
#include "context/ApplicationContext.h"

int main(int argc, char *argv[]) {
  try {
    // Initialize the Application Context
    ApplicationContext appCtx(argc, argv);
    // Immediately begin the loading animation
    // thread upon program start.
    appCtx.threadManager.startThread("loadingUI");

    // Create the command manager and execute
    CommandManager cmdManager;
    cmdManager.execute(appCtx);
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
