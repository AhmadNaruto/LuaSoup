# LuaSoup NRP: Multi-Language Usage Guide

This guide provides practical code examples for using **LuaSoup / Native Runtime Platform (NRP)** across C++, Luau, and Kotlin.

---

## 🔵 1. C++ Native Core API Usage

### Initialize Runtime Core & Luau Engine
```cpp
#include "nrp/core/runtime.hpp"
#include "nrp/luau/luau_engine.hpp"
#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/crypto.hpp"
#include <iostream>

int main() {
    // 1. Initialize Runtime Context
    nrp::Runtime runtime("android_arm64");
    runtime.initialize();

    // 2. HTML Parsing & CSS Querying
    auto doc = nrp::modules::html::Document::parse("<div class='item'><span>LuaSoup Engine</span></div>");
    auto node = doc->select_one(".item span");
    if (node) {
        std::cout << "Extracted Text: " << node->text() << std::endl;
    }

    // 3. JSON Parsing & Inspection
    auto json_val = nrp::modules::json::JSON::parse("{\"status\": \"active\", \"version\": 1.0}");
    std::cout << "Status: " << json_val["status"].as_string() << std::endl;

    // 4. Cryptographic Hashing
    std::string sha256_hash = nrp::modules::crypto::Crypto::sha256("Hello LuaSoup");
    std::cout << "SHA256: " << sha256_hash << std::endl;

    return 0;
}
```

---

## 🟡 2. Luau Scripting Engine Usage

### Running Sandboxed Luau Scripts
```cpp
#include "nrp/luau/luau_engine.hpp"

nrp::luau::LuauEngine engine;
engine.initialize();

// Evaluate expression returning a value
auto result = engine.eval("return 10 + 20 * 2");
if (result.is_number()) {
    double val = result.as_number(); // 50.0
}

// Evaluate string manipulation script
auto str_result = engine.eval("return string.upper('luasoup nrp')");
// "LUASOUP NRP"
```

### Exposing Native C++ Objects via Metatables to Luau
```cpp
// Metatable binding for object handles
engine.eval(R"(
    local doc = HTML.parse("<p id='title'>Welcome</p>")
    local title = doc:select("#title")
    print(title:text()) -- Outputs: "Welcome"
)");
```

---

## 🟢 3. Kotlin Android SDK Usage

### High-Level API (`LuaSoupEngine`)
```kotlin
import com.luasoup.nrp.LuaSoupEngine

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize Native Runtime Engine
        val engine = LuaSoupEngine.initialize()

        // 1. Parse HTML DOM
        val formattedHtml = engine.parseHtml("<div class='card'><h2>LuaSoup</h2></div>")

        // 2. Evaluate Luau Script
        val luauOutput = engine.evalLuau("return 'Result from Luau: ' .. (5 * 5)")

        println("Target ABI: ${engine.targetAbi}")
        println("Luau Result: $luauOutput")
    }
}
```

---

## 🛠 4. Compiling Custom Meta Specifications (`nrpc`)

Define your API specification file inside `specs/` (e.g., `specs/my_module.md`):

```markdown
# Module: MyModule

## Class: DataProcessor
- Method: process(input: String): String
- Property: status: String
```

Then run `nrpc` to re-generate C++ JNI bridge and Kotlin SDK bindings:

```bash
./build/nrpc specs/
```
