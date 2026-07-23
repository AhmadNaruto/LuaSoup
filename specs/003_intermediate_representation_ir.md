# Intermediate Representation (IR)

## Overview

The Intermediate Representation (IR) is the canonical representation of the Native Runtime Platform.

Every backend SHALL consume the IR rather than the original Meta Model.

The IR SHALL normalize every semantic construct into a platform-independent representation.

The IR SHALL remain stable regardless of source language.

---

## Objectives

The IR SHALL:

- Normalize metadata.
- Resolve inheritance.
- Resolve generic types.
- Resolve ownership.
- Resolve nullability.
- Resolve overloads.
- Resolve namespaces.
- Resolve documentation links.
- Resolve platform constraints.

Backends MUST NOT perform semantic analysis.

---

## Compilation Pipeline

```
Meta DSL

↓

Meta Model

↓

Semantic Analysis

↓

IR Builder

↓

Intermediate Representation

↓

Backend Toolchain
```

---

## Design Principles

The IR SHALL be:

- immutable
- deterministic
- language-independent
- implementation-independent
- backend-friendly

The IR SHALL never contain executable code.

---

## Module Representation

Each module SHALL contain:

- unique identifier
- namespace
- version
- dependencies
- capabilities
- exported types
- exported constants
- exported enumerations

---

## Type Representation

Every public type SHALL become an IR Type.

Supported kinds include:

- Primitive
- Class
- Interface
- Enumeration
- Flags
- Collection
- Generic
- Nullable
- Function
- Callback

Each type SHALL have a globally unique identifier.

---

## Symbol Table

The compiler SHALL generate a global symbol table.

Every public symbol SHALL have:

- identifier
- namespace
- qualified name
- owner
- visibility

Symbol lookup SHALL be deterministic.

---

## Namespace Resolution

Namespaces SHALL be fully resolved before backend generation.

Backends SHALL never resolve namespaces themselves.

---

## Inheritance Resolution

The compiler SHALL flatten inheritance information.

The IR SHALL expose complete inheritance trees.

Circular inheritance SHALL be rejected.

---

## Generic Resolution

Generic declarations SHALL be fully resolved.

Examples include:

- Array<Element>
- List<Node>
- Map<String, String>

Backends SHALL receive normalized generic information.

---

## Property Representation

Properties SHALL contain:

- identifier
- name
- type
- nullable
- readonly
- cached
- lazy
- ownership
- visibility
- documentation reference

---

## Method Representation

Methods SHALL contain:

- identifier
- parameters
- return type
- ownership
- overload identifier
- exception metadata
- documentation reference

---

## Parameter Representation

Every parameter SHALL define:

- name
- type
- nullable
- default value
- ownership
- variadic flag

---

## Constructor Representation

Constructors SHALL contain:

- visibility
- parameters
- ownership
- documentation

---

## Enumeration Representation

Enumerations SHALL contain:

- identifier
- values
- integer mapping
- documentation

---

## Constant Representation

Constants SHALL contain:

- identifier
- type
- value
- visibility
- documentation

---

## Documentation Representation

Documentation SHALL be stored separately from executable metadata.

Documentation SHALL include:

- summary
- description
- notes
- warnings
- examples
- references

Backends MAY format documentation differently.

---

## Example Representation

Examples SHALL become structured IR nodes.

Examples SHALL support automatic validation.

---

## Ownership Resolution

Ownership SHALL become explicit.

Supported ownership kinds:

- Shared
- Borrowed
- Unique
- Weak

Ownership SHALL influence generated bindings.

---

## Lifetime Resolution

Lifetime SHALL define:

- creator
- owner
- transfer policy
- destruction policy

Lifetime SHALL remain deterministic.

---

## Nullability Resolution

Every reference SHALL explicitly declare:

- nullable
- non-null

Implicit nullability is prohibited.

---

## Exception Resolution

Exception metadata SHALL contain:

- identifier
- hierarchy
- documentation
- platform mapping

---

## Capability Resolution

Modules SHALL expose normalized capabilities.

Examples:

- html.parser
- html.selector
- regex.compiler
- crypto.hash
- javascript.runtime

Capabilities SHALL be globally unique.

---

## Dependency Graph

The compiler SHALL generate a dependency graph.

The graph SHALL describe:

- module dependencies
- class dependencies
- interface dependencies
- runtime dependencies

Dependency cycles SHALL be rejected.

---

## Reflection Export

The Reflection Model SHALL be generated from the IR.

Reflection generation SHALL never access the Meta Model directly.

---

## Backend Contract

Every backend SHALL consume exactly the same IR.

Backend-specific behavior SHALL remain minimal.

---

## Stability

The IR SHALL remain stable across compiler revisions whenever practical.

Compiler optimizations MUST NOT alter observable API behavior.

---

