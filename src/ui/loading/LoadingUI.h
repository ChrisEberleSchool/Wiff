#pragma once

#include <thread>
#include <atomic>


class LoadingUI {
public:
    LoadingUI();
    ~LoadingUI();

    LoadingUI(const LoadingUI&) = delete;
    LoadingUI& operator=(const LoadingUI&) = delete;

    void stop();
private:
    void run(std::stop_token stoken);

    std::jthread worker_;
};
