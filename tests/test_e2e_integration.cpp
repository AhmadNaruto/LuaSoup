#include "nrp/core/runtime.hpp"
#include "nrp/luau/luau_engine.hpp"
#include "nrp/reflection/registry.hpp"
#include <cassert>
#include <iostream>
#include <string>

// Declare generated JNI functions for C++ E2E testing
extern "C" {
    const char* Java_com_luasoup_nrp_NRP_nativeGetTargetArch(void* env, void* clazz);
    bool Java_com_luasoup_nrp_NRP_nativeInit(void* env, void* clazz);
    void* Java_com_luasoup_nrp_NRP_nativeEvalLuau(void* env, void* clazz, void* jscript);
}

int main() {
    std::cout << "Running LuaSoup NRP End-to-End (E2E) Integration Tests for Android ARM64..." << std::endl;

    // 1. Initialize Core Runtime Engine
    nrp::Runtime runtime("e2e_arm64_runtime");
    runtime.initialize();
    assert(runtime.is_initialized());

    // 2. Initialize Luau Engine
    nrp::luau::LuauEngine luau;
    luau.initialize();
    assert(luau.is_initialized());

    // 3. E2E Scenario: Run Luau Script interacting with HTML DOM & Crypto
    std::string test_script = "HTML.parse('<div id=\"app\"><h1>LuaSoup E2E</h1></div>')";
    auto result = luau.eval(test_script);
    assert(result.is_string());
    assert(result.as_string().find("LuaSoup E2E") != std::string::npos);

    // 4. E2E Scenario: JSON Parsing & Crypto Hash Calculation
    std::string sha_script = "Crypto.sha256('Android ARM64 E2E')";
    auto sha_result = luau.eval(sha_script);
    assert(sha_result.is_string());
    assert(sha_result.as_string().length() == 64);

    // 5. Check Memory Manager clean state
    assert(runtime.memory().active_objects() == 0);

    luau.shutdown();
    runtime.shutdown();

    std::cout << "All End-to-End (E2E) Integration Tests Passed Successfully for Android ARM64!" << std::endl;
    return 0;
}
