# LuaSoup / Native Runtime Platform (NRP)

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![Target ABI](https://img.shields.io/badge/ABI-Android_ARM64-green.svg)](https://developer.android.com/ndk)
[![Luau Engine](https://img.shields.io/badge/Scripting-Luau_VM-00A2FF.svg)](https://luau.org/)
[![Kotlin SDK](https://img.shields.io/badge/Kotlin-SDK-7F52FF.svg)](https://kotlinlang.org/)

LuaSoup (Native Runtime Platform - NRP) is a high-performance, cross-language runtime environment, C++20 engine, and compiler infrastructure designed for Android ARM64 and native targets. It seamlessly bridges a high-throughput C++ Native Core, an embedded sandboxed Luau scripting engine, and an idiomatic Android Kotlin SDK.

---

## 🌟 Key Features

- **Unified Memory Architecture**: Deterministic handle management, atomic reference counting, memory pooling, and zero-copy byte buffers.
- **Embedded Luau VM**: Fast, sandboxed Luau execution with memory limits, timeouts, and native C++ metatable/userdata bindings (`__index`, `__newindex`, `__call`, `__gc`, `__eq`).
- **NRP Compiler (`nrpc`)**: Automated Interface Definition Language (IDL) AST parser, semantic analyzer, and multi-backend code generator (JNI, Reflection, Kotlin SDK, Luau definitions).
- **Zero Handwritten JNI**: 100% of JNI glue code is auto-generated directly from formal specifications.
- **Core Built-in Modules**:
  - 🌐 **HTML / DOM**: High-speed Lexbor-powered HTML5 DOM parser, tree operations, and CSS selectors.
  - 📦 **JSON**: Ultra-fast JSON parser, DOM inspector, and serializer.
  - 🔍 **Regex**: Optimized C++ RE2 regular expression matching engine.
  - 🔒 **Crypto**: Hashing (SHA256, MD5), HMAC, and AES encryption utilities.
  - 🌐 **URL, Encoding & Buffer**: URL parsing/formatting, Base64/Hex conversion, and direct byte buffer management.
  - ⚡ **JS Execution**: Sandboxed QuickJS execution runtime.
- **Fluent DSL Engine**: Type-safe DSL builders for HTML, JSON, and query pipeline fusion in both Luau and Kotlin.

---

## 🏗 System Architecture

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           Kotlin Android SDK                            │
│           (Public SDK, Idiomatic Wrappers, Coroutine Bridge)            │
└────────────────────────────────────┬────────────────────────────────────┘
                                     │ (JNI Bridge Engine / Zero-Copy)
┌────────────────────────────────────▼────────────────────────────────────┐
│                              Runtime Core                               │
│  (Lifecycle, Handles, Memory Architecture, Service Registry, Reflection)│
└──────────┬───────────────────────────────────────────────────┬──────────┘
           │                                                   │
┌──────────▼───────────────────────────┐         ┌─────────────▼──────────┐
│             Luau Engine              │         │  Built-in Native Modules│
│  (Scripting VM, Sandboxed Exec,      │         │ (HTML/DOM, JSON, Crypto│
│   Userdata & Metatable Bindings)     │         │  Regex, Buffer, URL)   │
└──────────────────────────────────────┘         └────────────────────────┘
                                     ▲
                                     │ (Generated Artifacts)
┌────────────────────────────────────┴────────────────────────────────────┐
│                    NRP Compiler & IR Infrastructure                     │
│         (Meta Model → Semantic Analysis → IR → Backend Generators)      │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 🛠 Quick Start & Build Instructions

### Prerequisites
- CMake `3.22+`
- C++20 compliant compiler (GCC / Clang)
- Ninja / Make build tools

### Build & Run Native Tests
```bash
# Generate build configuration
cmake -B build -S .

# Build libraries, executables, and tests
cmake --build build

# Execute full test suite (7/7 suites)
ctest --test-dir build --output-on-failure
```

### Run NRP Compiler (`nrpc`)
```bash
./build/nrpc specs/
```

---

## 📁 Repository Layout

```
.
├── CMakeLists.txt              # Root CMake build configuration
├── PLANNING.md                 # System architecture and roadmap checklist
├── README.md                   # Project overview (this file)
├── USAGE.md                    # Detailed multi-language API reference
├── compiler/                   # NRP Compiler (nrpc) AST, IR & Backend Generators
├── include/nrp/                # Core C++ public headers (Core, Luau, Modules, Bridge, DSL)
├── src/                        # Native C++ implementation files
├── kotlin/luasoup-sdk/         # Android Kotlin SDK wrapper & unit tests
├── specs/                      # Specification module files parsed by nrpc
├── generated/                  # Generated JNI bridge & Reflection descriptors
├── third_party/                # Third-party engines (Luau, Lexbor, RE2, MbedTLS, QuickJS)
└── tests/                      # C++ unit & integration tests
```

---

## 📖 License

LuaSoup / Native Runtime Platform is open-source under the MIT License.
