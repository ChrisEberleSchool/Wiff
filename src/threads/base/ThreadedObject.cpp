#include "ThreadedObject.h"


ThreadedObject::ThreadedObject() = default;

ThreadedObject::~ThreadedObject() {
    stop();
}


void ThreadedObject::start() {
    if (!worker_.joinable()) {
        worker_ = std::jthread([this](std::stop_token stoken) {
            this->run(stoken);
        });
    }
}


void ThreadedObject::stop() {
    if (worker_.joinable()) {
        worker_.request_stop();
        worker_.join();
    }
}
