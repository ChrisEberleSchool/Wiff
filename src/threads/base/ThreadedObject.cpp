#include "ThreadedObject.h"

ThreadedObject::ThreadedObject() = default;

ThreadedObject::~ThreadedObject() {
    stop();
}

void ThreadedObject::start() {
    if (!worker_.joinable()) {
        worker_ = std::jthread(&ThreadedObject::run, this, std::placeholders::_1);
    }
}

void ThreadedObject::stop() {
    if (worker_.joinable()) {
        worker_.request_stop();
        worker_.join();
    }
}
