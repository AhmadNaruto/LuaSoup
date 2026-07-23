# Kotlin Binding Framework

## Overview

The Kotlin Binding Framework provides the official Android SDK for the Native Runtime Platform.

The Kotlin API SHALL expose an idiomatic Kotlin programming model while preserving semantic parity with the native runtime.

Applications SHALL interact exclusively with the Kotlin SDK.

JNI SHALL remain completely hidden.

---

## Design Goals

The Kotlin Binding Framework SHALL provide:

- idiomatic Kotlin APIs
- zero handwritten bindings
- automatic code generation
- predictable ownership
- minimal allocations
- coroutine compatibility
- Android-first design

Every generated API SHALL remain consistent with the Luau API.

---

## Architecture

```
             Meta Framework

                   │

                   ▼

          Intermediate Representation

                   │

                   ▼

          Kotlin Backend Generator

                   │

                   ▼

          Generated Kotlin SDK

                   │

                   ▼

        Native Bridge Engine

                   │

                   ▼

              Runtime Core
```

---

## Public API

The Kotlin SDK SHALL become the only public interface for Android applications.

Applications MUST NOT access:

- JNI
- native pointers
- generated JNI bindings
- runtime internals

---

## Runtime API

Applications SHALL create Runtime instances through the Kotlin SDK.

Example API:

```
Runtime.create()

Runtime.close()

Runtime.builder()
```

The Runtime SHALL implement AutoCloseable.

---

## Module Access

Modules SHALL be exposed as Runtime properties.

Example:

```
runtime.html

runtime.json

runtime.regex

runtime.crypto

runtime.javascript
```

Module lookup SHALL execute in constant time.

---

## Object Model

Every generated object SHALL behave like a native Kotlin object.

Objects SHALL expose:

- properties
- functions
- collections
- iterators

Getter-style APIs SHOULD be avoided whenever Kotlin properties are appropriate.

---

## Property Mapping

Native properties SHALL become Kotlin properties.

Examples include:

```
document.title

document.body

element.text

element.html

element.parent
```

Generated getters SHALL remain transparent.

---

## Function Mapping

Native methods SHALL become Kotlin member functions.

Function names SHALL remain consistent across Kotlin and Luau whenever practical.

---

## Nullability

Generated Kotlin APIs SHALL preserve nullability.

Nullable native values SHALL become nullable Kotlin types.

Implicit platform types are prohibited.

---

## Collections

Generated collection types SHALL expose Kotlin Collection interfaces.

Supported interfaces include:

- Iterable
- Collection
- List
- Set
- Map

Collections SHALL remain read-only unless mutation is explicitly supported.

---

## Native Collections

Native collections SHALL expose specialized wrapper classes.

Examples include:

- Elements
- JsonArray
- JsonObject

These wrappers MAY additionally implement Kotlin Collection interfaces.

---

## Lazy Evaluation

Expensive native objects SHOULD remain lazily evaluated.

Accessing one property SHALL NOT eagerly load unrelated data.

---

## Wrapper Identity

Every native object SHALL map to exactly one Kotlin wrapper within the same Runtime whenever practical.

Repeated access SHOULD reuse existing wrappers.

---

## Equality

Generated wrappers SHALL distinguish:

- identity equality
- structural equality

Identity SHALL correspond to the underlying native object.

---

## Ownership

Wrapper ownership SHALL follow native ownership semantics.

Ownership SHALL remain invisible to application developers.

Generated bindings SHALL enforce ownership automatically.

---

## Lifetime

Wrapper lifetime SHALL remain synchronized with native lifetime.

Destroyed native objects SHALL invalidate their wrappers.

Invalid wrappers SHALL throw deterministic exceptions.

---

## Exception Mapping

Native exceptions SHALL become Kotlin exceptions.

Exception hierarchy SHALL remain deterministic.

Generated APIs SHALL use typed exceptions whenever possible.

---

## Coroutine Compatibility

Blocking native operations SHOULD expose coroutine-friendly APIs.

Generated bindings MAY provide suspend functions.

Coroutine support SHALL remain optional.

---

## Extension Functions

Generated APIs MAY include Kotlin extension functions.

Extensions SHALL never modify native semantics.

Extensions SHALL remain allocation-free whenever practical.

---

## Value Classes

Small immutable wrappers SHOULD use Kotlin value classes whenever practical.

Examples include:

- Handle
- Identifier
- Version

---

## Inline Functions

Generated helper functions SHOULD be inline whenever beneficial.

Inlining SHALL reduce wrapper overhead.

---

## Builder APIs

Complex object construction SHOULD use builder APIs.

Builders SHALL remain immutable after construction.

---

## DSL Compatibility

Generated bindings SHALL integrate naturally with Kotlin DSL syntax.

DSL builders SHALL remain type-safe.

---

## Documentation

Generated Kotlin APIs SHALL contain documentation generated from the Meta Framework.

Manual documentation duplication is prohibited.

---

## IDE Support

Generated APIs SHALL support:

- autocomplete
- navigation
- quick documentation
- refactoring
- signature help

---

## Android Compatibility

The Kotlin SDK SHALL remain compatible with Android development practices.

Bindings SHALL avoid unnecessary reflection.

Bindings SHALL avoid dynamic proxies.

Bindings SHALL remain compatible with R8 and ProGuard.

---

## Binary Compatibility

Public Kotlin APIs SHOULD remain binary compatible across minor releases whenever practical.

Breaking changes SHALL require major version increments.

---

## Performance Goals

Generated Kotlin bindings SHALL prioritize:

- wrapper reuse
- inline access
- zero-copy
- lazy evaluation
- minimal JNI transitions
- allocation-free property access whenever practical

---

## Generated Source Policy

Every Kotlin binding SHALL be generated automatically.

Handwritten public bindings are prohibited.

Developers SHALL modify the Meta Framework instead of generated Kotlin sources.

---

## Kotlin Binding Invariants

The Kotlin Binding Framework SHALL guarantee:

- every wrapper belongs to exactly one Runtime
- every wrapper represents exactly one native object
- wrapper identity remains stable
- nullability is explicit
- ownership remains deterministic
- public APIs originate exclusively from generated metadata
- generated bindings remain the official Android SDK


