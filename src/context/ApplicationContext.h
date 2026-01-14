#pragma once

#include <argument/ParsedArgs.h>
#include <threads/manager/ThreadManager.h>

#include "threads/loading/LoadingThread.h"

/**
 * @brief This class holds application context specific
 *        objects that need to be accessed in multiple places.
 *
 * */
struct ApplicationContext {
  ApplicationContext(int argc, char *argv[]) : parsedArgs(argc, argv) {
    this->threadManager.add("loadingUI", std::make_unique<LoadingThread>());
  }

  ThreadManager threadManager;
  ParsedArgs parsedArgs;
};
