# Backend Pipeline

## Overview

Every backend SHALL consume the same Intermediate Representation.

Backends SHALL remain independent.

Backends SHALL NOT communicate with one another.

---

## Runtime Backend

The Runtime Backend SHALL generate:

- module registry
- reflection registry
- type registry
- descriptor tables
- dispatch tables
- runtime metadata

---

## Kotlin Backend

The Kotlin Backend SHALL generate:

- public SDK
- wrappers
- extension APIs
- builders
- Kotlin documentation
- collection adapters

Generated APIs SHALL remain idiomatic.

---

## Luau Backend

The Luau Backend SHALL generate:

- module registration
- userdata bindings
- property bindings
- method bindings
- iterator bindings
- operator bindings
- constant bindings

Generated APIs SHALL preserve Kotlin semantics.

---

## JNI Backend

The JNI Backend SHALL generate:

- native registration
- bridge functions
- converters
- ownership adapters
- exception adapters

Handwritten JNI is prohibited.

---

## Reflection Backend

The Reflection Backend SHALL generate:

- reflection descriptors
- metadata tables
- symbol tables
- lookup indexes

Reflection SHALL remain immutable.

---

## Documentation Backend

The Documentation Backend SHALL generate:

- Markdown
- HTML
- API Reference
- Module Guide
- Examples
- Version History

Documentation SHALL originate exclusively from metadata.

---

## Test Backend

The Test Backend SHALL generate:

- unit tests
- integration tests
- metadata validation
- API validation
- bridge validation

Generated tests SHALL verify generated bindings.

---

## Benchmark Backend

The Benchmark Backend SHALL generate:

- startup benchmarks
- parser benchmarks
- selector benchmarks
- regex benchmarks
- JSON benchmarks
- bridge benchmarks

Benchmark generation SHALL be automatic.

---

## Build Backend

The Build Backend SHALL generate:

- CMake fragments
- Gradle integration
- module manifests
- dependency manifests

Build files SHALL remain deterministic.

---

