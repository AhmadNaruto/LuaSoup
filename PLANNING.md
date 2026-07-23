# Master Implementation Plan: LuaSoup / Native Runtime Platform (NRP)

## System Overview

LuaSoup (Native Runtime Platform - NRP) is a high-performance, cross-language runtime environment and compiler infrastructure designed for Android and native targets. It seamlessly bridges C++ Native Core execution, Luau scripting engine, and Android Kotlin SDK using automated code generation, zero-copy memory buffers, and a unified reflection metadata system.

---

## Architecture Map

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

## Execution Phases & Roadmap

### Phase 1: Core Foundation & Build System Setup
- [x] Initialize CMake build configuration for C++20 native engine.
- [x] Set up Gradle version catalog (`gradle/libs.versions.toml`) and Kotlin project structure.
- [x] Configure target C++ compiler flags (`-std=c++20`, `-Wall`, `-Wextra`, `-fvisibility=hidden`).
- [x] Implement core utilities: logging, fixed-size allocators, atomic reference counting, and platform abstraction headers.

### Phase 2: Memory Architecture & Runtime Core
- [x] **Native Memory Management**: Implement deterministic object handles, reference counting, memory pools, and borrowing semantics.
- [x] **Runtime Instance Lifecycle**: Create `Runtime` core execution engine, thread isolation, and resource cleanup context.
- [x] **Runtime Services Manager**: Implement modular service registry (Memory Service, Cache Service, Type Service, Diagnostics Service).

### Phase 3: Type System, Reflection System & ABI Layer
- [x] **Unified Type System**: Define primitive types, object descriptors, collection types, and function signature descriptors.
- [x] **Reflection Metadata Registry**: Implement immutable runtime symbol table, property descriptors, method descriptors, and attribute registry.
- [x] **Stable C/C++ ABI Contract**: Define binary C-ABI boundary for interop with native plugins and generated bindings.

### Phase 4: Native Bridge Engine (C++ <-> JNI <-> Kotlin)
- [x] **JNI Engine Abstraction**: Implement safe C++ wrapper for JNI environment, global/local reference management, and exception translation.
- [x] **Deep Automatic Conversion**: Implement recursive conversion for primitive types, strings, lists, maps, and native handles between C++ and JVM.
- [x] **Zero-Copy Memory Buffer**: Support direct `ByteBuffer` sharing between Java/Kotlin and C++ native memory.

### Phase 5: Luau Scripting Engine Integration
- [x] **Luau VM Embedding**: Build and link Luau VM into native core runtime.
- [x] **Sandboxed Environment**: Configure memory limits, execution timeouts, and restricted global environments.
- [x] **Luau Bindings & Metatables**: Implement automatic binding mechanism for exposing C++ native objects and methods as Luau userdata with metatables (`__index`, `__newindex`, `__call`, `__gc`, `__eq`).

### Phase 6: NRP Compiler & Code Generation Framework
- [x] **Meta DSL & AST Parser**: Implement Interface Definition Language (IDL) parser and Meta DSL builder.
- [x] **Semantic Analyzer**: Validate duplicate symbols, cyclic inheritance, ownership violations, and type compatibility.
- [x] **Intermediate Representation (IR)**: Implement canonical platform-independent IR data structures.
- [x] **Backend Code Generators**:
  - [x] **Kotlin Generator**: Produce idiomatic Kotlin SDK classes, extension methods, and coroutines bindings.
  - [x] **Luau Generator**: Produce Luau module registrations and type definitions.
  - [x] **JNI Generator**: Generate boilerplate C++ JNI bridge glue without handwritten JNI code.
  - [x] **Reflection Generator**: Produce C++ metadata tables.
  - [x] **Documentation Generator**: Generate API Markdown/HTML docs from metadata.

### Phase 7: Built-in Core Native Modules
- [x] **HTML / DOM Module**: Implement HTML parser, tree structure, CSS selector engine, DOM manipulation, and HTML builder.
- [x] **JSON Module**: High-performance streaming/DOM JSON parser and serializer.
- [x] **Regex Module**: High-performance regular expression matching engine.
- [x] **Crypto Module**: Hashing (SHA256, MD5), HMAC, AES encryption utilities.
- [x] **URL, Encoding & Buffer Modules**: URL parsing/formatting, Base64/Hex encoding, and mutable byte buffers.

### Phase 8: DSL Framework & High-Level APIs
- [x] **Fluent DSL Builders**: Implement fluent, type-safe DSL framework in Kotlin and Luau for HTML construction, JSON manipulation, and query pipelines.
- [x] **Query & Pipeline Fusion**: Optimize chained DSL calls into compiled native execution plans.

### Phase 9: Verification, Benchmarks & Error Handling
- [x] **Error Architecture**: Implement structured error codes, diagnostic context, stack trace capture, and exception propagation across C++, Luau, and Kotlin.
- [x] **Automated Test Suite**: Unit tests, integration tests, cross-language interop tests, and memory leak detection (ASan/Valgrind).
- [x] **Benchmark Suite**: Measure startup latency, JNI bridge invocation throughput, Luau script execution speed, and parser throughput.

---

## Success Criteria

1. **Zero Memory Leaks**: All native objects managed via handles with deterministic cleanup.
2. **Zero Handwritten JNI**: 100% of JNI interop code generated directly from IDL/IR.
3. **Language Parity**: Identical module functionality and API semantics available in both Kotlin and Luau.
4. **Performance Targets**: Minimal overhead across JNI boundary, fast cold startup time, and high-throughput DOM/JSON parsing.
