#include "nrp/core/runtime.hpp"
#include <iostream>

namespace nrp {

Runtime::Runtime(std::string id) : id_(std::move(id)) {}

Runtime::~Runtime() {
    if (initialized_) {
        shutdown();
    }
}

void Runtime::initialize() {
    if (initialized_.exchange(true)) return;
    // Perform Core Runtime initialization
}

void Runtime::shutdown() {
    if (!initialized_.exchange(false)) return;
    services().shutdown_all();
    memory().reset();
}

} // namespace nrp
