#pragma once

#include "threads/base/ThreadedObject.h"

class LoadingThread : public ThreadedObject {
public:
  LoadingThread() = default;
  ~LoadingThread() override = default;

  // Disable copy and assignment
  LoadingThread(const LoadingThread &) = delete;
  LoadingThread &operator=(const LoadingThread &) = delete;

protected:
  // Thread function
  void run(std::stop_token stoken) override;
};
