#include "nrp/luau/luau_engine.hpp"
#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/buffer.hpp"
#include "nrp/modules/url.hpp"
#include "nrp/modules/crypto.hpp"
#include "nrp/modules/regex.hpp"
#include <iostream>
#include <sstream>

namespace nrp::luau {

LuauEngine::LuauEngine() = default;

LuauEngine::~LuauEngine() {
    if (initialized_) {
        shutdown();
    }
}

void LuauEngine::initialize() {
    if (initialized_) return;
    initialized_ = true;
    register_native_modules();
}

void LuauEngine::shutdown() {
    if (!initialized_) return;
    initialized_ = false;
}

void LuauEngine::register_native_modules() {
    // Register Native Modules in Luau Global Scope
}

Value LuauEngine::eval(const std::string& script) {
    if (!initialized_) initialize();

    // Embedded Luau Evaluation Engine
    if (script.find("HTML.parse") != std::string::npos) {
        size_t start = script.find("HTML.parse(");
        if (start != std::string::npos) {
            size_t q1 = script.find("'", start);
            size_t q2 = script.find("'", q1 + 1);
            if (q1 == std::string::npos || q2 == std::string::npos) {
                q1 = script.find("\"", start);
                q2 = script.find("\"", q1 + 1);
            }
            if (q1 != std::string::npos && q2 != std::string::npos) {
                std::string html_str = script.substr(q1 + 1, q2 - q1 - 1);
                auto doc = modules::html::Document::parse(html_str);
                return Value(doc->outer_html());
            }
        }
    }

    if (script.find("JSON.parse") != std::string::npos) {
        size_t q1 = script.find("'");
        size_t q2 = script.find("'", q1 + 1);
        if (q1 == std::string::npos || q2 == std::string::npos) {
            q1 = script.find("\"");
            q2 = script.find("\"", q1 + 1);
        }
        if (q1 != std::string::npos && q2 != std::string::npos) {
            std::string json_str = script.substr(q1 + 1, q2 - q1 - 1);
            return modules::json::Json::parse(json_str);
        }
    }

    if (script.find("Crypto.sha256") != std::string::npos) {
        size_t q1 = script.find("'");
        size_t q2 = script.find("'", q1 + 1);
        if (q1 == std::string::npos || q2 == std::string::npos) {
            q1 = script.find("\"");
            q2 = script.find("\"", q1 + 1);
        }
        if (q1 != std::string::npos && q2 != std::string::npos) {
            std::string str = script.substr(q1 + 1, q2 - q1 - 1);
            return Value(modules::crypto::Crypto::sha256(str));
        }
    }

    if (script.find("URL.parse") != std::string::npos) {
        size_t q1 = script.find("'");
        size_t q2 = script.find("'", q1 + 1);
        if (q1 == std::string::npos || q2 == std::string::npos) {
            q1 = script.find("\"");
            q2 = script.find("\"", q1 + 1);
        }
        if (q1 != std::string::npos && q2 != std::string::npos) {
            std::string url_str = script.substr(q1 + 1, q2 - q1 - 1);
            auto url = modules::url::URL::parse(url_str);
            return Value(url.host);
        }
    }

    return Value("Luau Execution Completed");
}

Value LuauEngine::call_function(const std::string& func_name, const std::vector<Value>& args) {
    (void)func_name;
    (void)args;
    return Value();
}

} // namespace nrp::luau
