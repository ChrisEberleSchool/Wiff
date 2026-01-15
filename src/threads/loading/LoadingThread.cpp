#include "LoadingThread.h"

#include <iostream>

void LoadingThread::run(std::stop_token stoken) {
  const char spinner[] = {'|', '/', '-', '\\'};
  std::size_t i = 0;
  using namespace std::chrono_literals;

  while (!stoken.stop_requested()) {
    std::cout << "\rLoading " << spinner[i++ % 4] << std::flush;
    std::this_thread::sleep_for(100ms);
  }

  // Clear the line when done
  std::cout << "\r              \r" << std::flush;
}
