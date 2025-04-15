
#include "signal_handler.hpp"
#include <csignal>
#include <atomic>

static std::atomic<bool> interrupted = false;

void handler(int) {
    interrupted = true;
}

void setup_signal_handler() {
    std::signal(SIGINT, handler);
}

bool is_interrupted() {
    return interrupted;
}
