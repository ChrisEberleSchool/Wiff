#include "./ThreadManager.h"


void ThreadManager::add(const std::string& threadName, std::unique_ptr<ThreadedObject> thread) {
    threads.insert(threadName, std::move(thread));
}

void ThreadManager::startThread(const std::string& threadName) {
    auto it = threads.find(threadName);

    if(it != threads.end()) {
        it->second->start();
    }
}
void ThreadManager::stopThread(const std::string& threadName) {
    auto it = threads.find(threadName);

    if(it != threads.end()) {
        it->second->stop();
    }
}

