# Native Bridge Engine

## Overview

The Native Bridge Engine is the communication layer between the Runtime Core and external languages.

The Bridge SHALL provide a unified object exchange mechanism for:

- Kotlin
- Luau
- Future language bindings

The Bridge SHALL abstract JNI completely.

Applications SHALL never interact with JNI directly.

---

## Design Goals

The Native Bridge Engine SHALL provide:

- zero-copy whenever practical
- deterministic ownership
- automatic type conversion
- object identity preservation
- minimal JNI transitions
- platform-independent semantics

The Bridge SHALL expose identical behavior across every supported language.

---

## Architecture

```
                Runtime Core

                     │

                     ▼

          Native Bridge Engine

      ┌──────────────┼──────────────┐

      ▼              ▼              ▼

 Identity      Type System     Converters

      ▼              ▼              ▼

 Object Pool   Bridge Cache    JNI Layer

                     │

          ┌──────────┴──────────┐

          ▼                     ▼

     Kotlin API            Luau API
```

---

## Responsibilities

The Native Bridge Engine SHALL manage:

- object conversion
- primitive conversion
- collection conversion
- ownership transfer
- object identity
- reference tracking
- bridge caching
- exception translation

---

## Bridge Session

Every API invocation SHALL execute inside a Bridge Session.

A Bridge Session SHALL own:

- temporary allocations
- temporary references
- conversion cache
- exception context

Temporary resources SHALL be released automatically when the session completes.

---

## Type Conversion

The Bridge SHALL automatically convert supported types.

Primitive types include:

- Boolean
- Int
- Long
- Float
- Double
- String
- ByteArray

Complex types include:

- Array
- List
- Map
- Native Object
- JSON Object
- JSON Array

---

