#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "threads/base/ThreadedObject.h"

class ThreadManager {
public:
    ThreadManager();
    ~ThreadManager();

    void add(const std::string& threadName, std::unique_ptr<ThreadedObject> thread);
    
    void startThread(const std::string& threadName);
    void stopThread(const std::string& threadName);

private:
    std::unordered_map<std::string, ThreadedObject> threads;
};
