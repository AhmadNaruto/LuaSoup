#include "nrp/core/runtime.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Running Runtime Core Tests..." << std::endl;

    nrp::Runtime runtime("test_env");
    assert(!runtime.is_initialized());

    runtime.initialize();
    assert(runtime.is_initialized());
    assert(runtime.id() == "test_env");

    runtime.shutdown();
    assert(!runtime.is_initialized());

    std::cout << "Runtime Core Tests Passed!" << std::endl;
    return 0;
}
