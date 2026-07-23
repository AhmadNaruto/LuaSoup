# Backend Toolchain

## Overview

The Backend Toolchain transforms the Intermediate Representation into language-specific artifacts.

Each backend SHALL consume only the IR.

Backends SHALL remain completely independent from one another.

---

## Kotlin Backend

The Kotlin Backend SHALL generate:

- public SDK
- Kotlin wrappers
- package structure
- documentation comments
- extension functions
- collection adapters

Generated APIs SHALL follow idiomatic Kotlin conventions.

---

## Luau Backend

The Luau Backend SHALL generate:

- module registration
- userdata descriptors
- property bindings
- method bindings
- iterator bindings
- operator bindings

Generated APIs SHALL remain consistent with Kotlin APIs.

---

## JNI Backend

The JNI Backend SHALL generate:

- native method declarations
- native registration tables
- type conversion adapters
- exception bridges
- ownership bridges

Handwritten JNI SHALL be minimized.

---

## Runtime Backend

The Runtime Backend SHALL generate:

- module registry
- reflection registry
- type registry
- property tables
- method tables

Runtime initialization SHALL be automatic.

---

## Documentation Backend

The Documentation Backend SHALL generate:

- Markdown
- API reference
- examples
- module documentation
- version history

Documentation SHALL always originate from metadata.

---

## Test Backend

The Test Backend SHALL generate:

- unit tests
- integration tests
- API validation
- metadata validation

Generated tests SHALL validate generated bindings.

---

## Benchmark Backend

The Benchmark Backend SHALL generate:

- performance benchmarks
- allocation benchmarks
- throughput benchmarks
- startup benchmarks

---

## Future Backends

The architecture SHALL allow additional backends without modifying the compiler frontend.

Examples include:

- Swift
- Rust
- C
- C#
- TypeScript
- Python

---

## Backend Independence

Backends SHALL NOT communicate with one another.

Every backend SHALL consume only the IR.

This guarantees deterministic generation.

---

## Incremental Generation

The compiler SHOULD support incremental generation.

Only modified metadata SHOULD trigger regeneration.

---

## Deterministic Output

Identical metadata SHALL always produce identical generated output.

Generation SHALL be reproducible across supported platforms.

---

## Build Integration

The Backend Toolchain SHALL integrate with Gradle.

Generation SHALL execute automatically during the build process.

Generated sources SHALL participate in incremental compilation.

---

## Generated Source Policy

Generated files MUST NOT be modified manually.

Any manual modification SHALL be overwritten during the next generation.

Developers SHALL modify the Meta DSL instead of generated artifacts.

---

## Single Source of Truth

The Meta DSL SHALL remain the only editable definition of public APIs.

Every generated artifact SHALL originate from the Meta Framework through the compiler pipeline.

