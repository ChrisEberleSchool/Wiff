#include "./LoadingUI.h"

#include <iostream>
#include <chrono>

LoadingUI::LoadingUI()
    : worker_([this](std::stop_token stoken) { run(stoken); })
{
}

LoadingUI::~LoadingUI() {
    stop();
}

void LoadingUI::stop() {
    if (worker_.joinable()) {
        worker_.request_stop();
        // jthread auto-joins
    }
}

void LoadingUI::run(std::stop_token stoken) {
    const char spinner[] = {'|', '/', '-', '\\'};
    std::size_t i = 0;

    using namespace std::chrono_literals;

    while (!stoken.stop_requested()) {
        std::cout << "\rLoading " << spinner[i++ % 4] << std::flush;
        std::this_thread::sleep_for(100ms);
    }

    // Clear spinner line
    std::cout << "\r              \r" << std::flush;
}
