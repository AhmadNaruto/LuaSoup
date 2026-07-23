# Reflection System

## Overview

The Reflection System is the runtime metadata database of the Native Runtime Platform.

Every public object exposed by the Runtime SHALL be represented in the Reflection System.

Reflection SHALL become the authoritative source of runtime metadata.

Reflection SHALL NOT depend on Kotlin, Luau, JNI, or any implementation-specific technology.

---

## Design Goals

The Reflection System SHALL provide:

- complete runtime metadata
- fast lookup
- deterministic behavior
- immutable descriptors
- zero manual registration
- backend independence

Reflection SHALL support both compile-time generation and runtime inspection.

---

## Reflection Pipeline

```
Meta DSL

↓

Semantic Analysis

↓

Intermediate Representation

↓

Reflection Generator

↓

Reflection Database

↓

Runtime
```

Reflection SHALL be generated automatically.

Manual Reflection construction is prohibited.

---

## Reflection Database

Every Runtime SHALL own exactly one Reflection Database.

The Reflection Database SHALL contain:

- modules
- namespaces
- classes
- interfaces
- methods
- properties
- constructors
- constants
- enumerations
- attributes
- capabilities
- documentation metadata

The Reflection Database SHALL become immutable after Runtime initialization.

---

## Reflection Identifiers

Every reflected object SHALL have a globally unique identifier.

Identifiers SHALL remain stable across Runtime execution.

Identifiers SHALL NOT depend on memory addresses.

---

## Module Reflection

Every module SHALL expose:

- identifier
- namespace
- version
- description
- dependencies
- capabilities
- exported types

---

## Class Reflection

Every class SHALL expose:

- identifier
- qualified name
- namespace
- visibility
- inheritance
- interfaces
- constructors
- methods
- properties
- operators
- documentation

---

## Interface Reflection

Interfaces SHALL expose:

- methods
- properties
- inherited interfaces
- documentation

---

## Method Reflection

Methods SHALL expose:

- identifier
- name
- parameters
- return type
- ownership
- exceptions
- attributes
- documentation

---

## Property Reflection

Properties SHALL expose:

- name
- type
- nullable
- readonly
- cached
- lazy
- attributes
- documentation

---

## Constructor Reflection

Constructors SHALL expose:

- parameters
- visibility
- ownership
- documentation

---

## Enumeration Reflection

Enumerations SHALL expose:

- values
- integer representation
- documentation

---

## Constant Reflection

Constants SHALL expose:

- identifier
- value
- type
- documentation

---

## Capability Reflection

Capabilities SHALL expose:

- identifier
- owning module
- description

Capability lookup SHALL execute in constant time whenever practical.

---

## Attribute Reflection

Every reflected object MAY contain attributes.

Examples include:

- deprecated
- experimental
- internal
- native-only
- unstable
- platform-specific

Attributes SHALL remain extensible.

---

## Documentation Reflection

Documentation SHALL become part of Reflection.

Reflection SHALL expose:

- summary
- description
- examples
- notes
- warnings
- references
- version history

Documentation SHALL remain immutable.

---

## Example Reflection

Examples SHALL be stored as structured metadata.

Examples MAY be executable.

Examples SHALL support automatic validation.

---

## Version Reflection

Every reflected entity SHALL expose:

- introduced version
- deprecated version
- removed version
- stability level

---

## Reflection Queries

The Runtime SHALL support efficient lookup by:

- identifier
- namespace
- module
- class
- method
- property
- capability

Reflection queries SHALL remain allocation-free whenever practical.

---

## Reflection Indexes

The Reflection Database SHALL maintain indexes for:

- module names
- type names
- method names
- property names
- capability identifiers

Indexes SHALL be constructed during initialization.

---

## Reflection Cache

Reflection lookups SHOULD use dedicated caches.

Reflection caches SHALL belong to the owning Runtime.

---

## Reflection Traversal

Reflection SHALL support hierarchical traversal.

Example hierarchy:

```
Module

↓

Class

↓

Method

↓

Parameter
```

Traversal SHALL remain deterministic.

---

## Runtime Introspection

The Runtime MAY inspect Reflection metadata internally.

Applications SHALL NOT modify Reflection data.

Reflection SHALL remain read-only.

---

## Compiler Integration

The Reflection Database SHALL originate exclusively from the Intermediate Representation.

Backends SHALL NOT construct Reflection independently.

---

## Generated Metadata

The following SHALL be generated automatically:

- type descriptors
- property descriptors
- method descriptors
- ownership metadata
- documentation
- version metadata

Manual descriptor implementation is prohibited.

---

## Reflection Serialization

Reflection MAY be serialized into compact binary form.

Serialized Reflection SHALL preserve:

- identifiers
- ownership
- documentation references
- version metadata

Serialization format SHALL remain implementation-independent.

---

## Future Compatibility

The Reflection System SHALL support future extensions without breaking existing metadata.

Unknown metadata SHALL be safely ignored by older Runtime versions whenever practical.

---

## Reflection Invariants

The Reflection System SHALL guarantee:

- exactly one descriptor per public type
- immutable metadata after initialization
- stable identifiers
- deterministic lookup
- generated metadata only
- implementation-independent descriptors
- Reflection originates exclusively from the compiler pipeline

