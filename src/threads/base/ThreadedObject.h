#pragma once

#include <thread>

class ThreadedObject {
public:
  ThreadedObject();
  virtual ~ThreadedObject();

  void start();
  void stop();

protected:
  virtual void run(std::stop_token stoken) = 0;

private:
  std::jthread worker_;
};
