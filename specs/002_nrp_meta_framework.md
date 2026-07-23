# NRP Meta Framework

## Overview

The NRP Meta Framework defines every public capability of the Native Runtime Platform.

Rather than manually implementing bindings, documentation, registration, and tooling, every public API SHALL be described declaratively through the Meta Framework.

The Meta Framework SHALL become the single source of truth for the entire platform.

---

## Design Goals

The Meta Framework SHALL:

- Describe public APIs.
- Describe runtime behavior.
- Describe ownership semantics.
- Describe object relationships.
- Describe module capabilities.
- Describe documentation.
- Describe examples.
- Describe testing metadata.
- Describe benchmarking metadata.

The Meta Framework SHALL NOT contain implementation logic.

---

## Architecture

```
Kotlin Meta DSL

        │

        ▼

 Meta Builder

        │

        ▼

 Meta Model

        │

        ▼

 Semantic Validation

        │

        ▼

 Reflection Model

        │

        ▼

 Intermediate Representation

        │

        ▼

 Backend Toolchain
```

---

## Meta Model

The Meta Model SHALL represent every public artifact of the platform.

Supported entities include:

- Modules
- Classes
- Interfaces
- Methods
- Properties
- Constructors
- Constants
- Enums
- Flags
- Exceptions
- Attributes
- Events
- Callbacks
- Examples
- Documentation
- Tests
- Benchmarks

The Meta Model SHALL remain language-independent.

---

## Module Descriptor

Every module SHALL declare:

- identifier
- namespace
- version
- description
- dependencies
- capabilities
- exported classes
- exported constants
- exported enums

Modules SHALL NOT expose implementation details.

---

## Class Descriptor

Every class SHALL describe:

- name
- namespace
- visibility
- documentation
- inheritance
- implemented interfaces
- constructors
- methods
- properties
- operators
- iterator support
- indexing support
- ownership model
- lifetime policy

---

## Property Descriptor

Every property SHALL declare:

- name
- type
- nullable
- readonly
- cached
- lazy
- observable
- documentation
- examples
- ownership

Properties SHALL support runtime reflection.

---

## Method Descriptor

Every method SHALL describe:

- name
- parameters
- return type
- ownership
- nullability
- overloads
- exceptions
- documentation
- examples
- benchmarks

Methods SHALL remain platform-independent.

---

## Constructor Descriptor

Constructors SHALL define:

- parameters
- ownership
- visibility
- validation rules

---

## Enum Descriptor

Enumerations SHALL define:

- values
- integer representation
- documentation

Enums SHALL be generated consistently across every language binding.

---

## Constant Descriptor

Constants SHALL define:

- name
- type
- value
- documentation

Constants SHALL become compile-time constants whenever possible.

---

## Interface Descriptor

Interfaces SHALL define:

- required methods
- required properties
- iterator behavior
- ownership expectations

Interfaces SHALL support multiple implementations.

---

## Exception Descriptor

Every exception SHALL define:

- identifier
- parent exception
- message template
- documentation

Exception metadata SHALL be available to every backend.

---

## Ownership Model

Every public object SHALL declare ownership semantics.

Supported ownership types include:

- Shared
- Unique
- Borrowed
- Weak

Ownership SHALL influence generated bindings.

---

## Lifetime Model

Objects SHALL define:

- runtime lifetime
- native lifetime
- ownership transfer
- destruction policy

Lifetime rules SHALL remain explicit.

---

## Nullability

Every parameter, property, and return type SHALL explicitly declare nullability.

Implicit nullability is prohibited.

---

## Generic Types

The Meta Framework SHALL support generic declarations.

Examples include:

- Array<Element>
- List<Node>
- Map<String, String>

Generic metadata SHALL remain available during compilation.

---

## Collection Metadata

Collection types SHALL describe:

- element type
- mutability
- iterator support
- indexing behavior

---

## Operator Metadata

Objects MAY expose operators.

Supported operators include:

- index
- equality
- iterator
- contains
- length

Operator behavior SHALL remain consistent across bindings.

---

## Attribute System

Descriptors MAY define custom attributes.

Examples:

- experimental
- deprecated
- internal
- unstable
- platform
- native-only

Backends MAY interpret attributes independently.

---

## Documentation Metadata

Documentation SHALL belong to metadata.

Documentation SHALL include:

- summary
- description
- notes
- warnings
- examples
- references

Documentation SHALL NOT be duplicated manually.

---

## Example Metadata

Examples SHALL become executable documentation.

Examples MAY be validated automatically during testing.

---

## Test Metadata

Metadata MAY define:

- unit tests
- integration tests
- validation rules
- expected outputs

Testing metadata SHALL remain independent of implementation.

---

## Benchmark Metadata

Metadata MAY define:

- workload
- iterations
- expected complexity
- memory expectations

Benchmark generation SHALL be automatic.

---

## Reflection Compatibility

Every descriptor SHALL become part of the Reflection Model.

Reflection SHALL expose complete runtime metadata.

Reflection SHALL remain immutable after runtime initialization.

---

## Semantic Validation

Compilation SHALL validate:

- duplicate declarations
- invalid ownership
- invalid inheritance
- cyclic references
- unresolved types
- invalid overloads
- namespace conflicts
- visibility violations

Compilation SHALL fail on semantic errors.

---

## Versioning

Every descriptor SHALL support:

- since
- deprecated
- removed
- experimental

Version metadata SHALL propagate to generated documentation.

---

## Platform Support

Metadata MAY specify supported platforms.

Examples:

- Android
- Linux
- Windows
- macOS
- iOS

Platform restrictions SHALL be validated during generation.

---

## Backend Independence

The Meta Model SHALL remain independent of:

- Kotlin
- Luau
- JNI
- C++
- Documentation
- Testing

Backends SHALL consume only the Intermediate Representation.

---

## Stability

The Meta Framework SHALL remain stable across compiler versions.

Future compiler improvements SHALL preserve metadata compatibility whenever practical.

