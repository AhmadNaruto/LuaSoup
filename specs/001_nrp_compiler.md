# NRP Compiler

## Overview

The NRP Compiler transforms Interface Definition Language (IDL) into runtime metadata and multiple implementation artifacts.

The compiler SHALL become the single source of truth for every public API exposed by the Native Runtime Platform.

Every binding, registration, documentation, and validation artifact SHALL be generated from the same semantic model.

Manual synchronization between different language bindings MUST NOT be required.

---

## Design Goals

The compiler SHALL:

- Parse NRP Interface Definition Language.
- Validate semantic correctness.
- Build a Reflection Model.
- Generate an Intermediate Representation (IR).
- Produce language-specific artifacts.
- Produce runtime registration metadata.
- Produce API documentation.
- Produce testing scaffolding.

The compiler MUST guarantee consistency across every generated output.

---

## Compilation Pipeline

The compiler SHALL execute the following pipeline.

```

IDL

↓

Lexer

↓

Parser

↓

Abstract Syntax Tree (AST)

↓

Semantic Analyzer

↓

Reflection Model

↓

Intermediate Representation (IR)

↓

Backend Generators

```

Every stage SHALL have a single responsibility.

---

## Source of Truth

The Interface Definition Language SHALL become the only manually maintained API description.

Developers MUST NOT manually duplicate:

- Kotlin bindings
- Luau bindings
- JNI registration
- Documentation
- Reflection metadata
- Test scaffolding

Every generated artifact SHALL originate from the IDL.

---

## Compiler Responsibilities

The compiler SHALL validate:

- duplicate names
- invalid inheritance
- invalid ownership
- invalid nullability
- invalid overloads
- invalid namespaces
- invalid property declarations
- invalid return types
- unsupported generic usage
- cyclic dependencies

Compilation SHALL fail if semantic validation fails.

---

## Intermediate Representation

The compiler SHALL transform semantic information into a language-independent Intermediate Representation.

The IR MUST contain:

- Modules
- Classes
- Interfaces
- Methods
- Properties
- Constructors
- Enums
- Constants
- Exceptions
- Documentation
- Ownership rules
- Lifetime rules
- Nullability
- Attributes

The IR MUST remain independent from every target language.

---

## Backend Independence

Backends MUST consume only the IR.

Backends MUST NOT access the AST directly.

This ensures every backend receives identical semantic information.


## Reflection Model

The Reflection Model describes every public runtime object.

The Reflection Model SHALL include:

- Modules
- Classes
- Interfaces
- Methods
- Properties
- Enums
- Constants
- Exceptions

Reflection metadata SHALL remain available during runtime.

Reflection SHALL become the foundation for:

- Binding generation
- Runtime validation
- Documentation generation
- Future IDE support
- Runtime introspection

Reflection SHALL NOT depend on Kotlin or Luau.


