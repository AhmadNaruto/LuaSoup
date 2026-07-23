#include "nrp/luau/luau_engine.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Running Luau Scripting Engine Tests..." << std::endl;

    nrp::luau::LuauEngine engine;
    engine.initialize();
    assert(engine.is_initialized());

    // 1. Test Luau HTML Parsing evaluation
    auto html_res = engine.eval("HTML.parse('<html><body><h1 class=\"title\">Hello Luau</h1></body></html>')");
    assert(html_res.is_string());
    assert(html_res.as_string().find("Hello Luau") != std::string::npos);

    // 2. Test Luau JSON Parsing evaluation
    auto json_res = engine.eval("JSON.parse('{\"framework\":\"LuaSoup\",\"arch\":\"arm64-v8a\"}')");
    assert(json_res.is_object());
    assert(json_res.as_object().at("framework").as_string() == "LuaSoup");

    // 3. Test Luau Crypto SHA-256 evaluation
    auto crypto_res = engine.eval("Crypto.sha256('LuaSoup ARM64')");
    assert(crypto_res.is_string());
    assert(crypto_res.as_string().length() == 64);

    // 4. Test Luau URL Parsing evaluation
    auto url_res = engine.eval("URL.parse('https://luasoup.dev/api/v1')");
    assert(url_res.is_string());
    assert(url_res.as_string() == "luasoup.dev");

    engine.shutdown();
    assert(!engine.is_initialized());

    std::cout << "Luau Scripting Engine Tests Passed Successfully!" << std::endl;
    return 0;
}
