# ABI (Application Binary Interface)

## Overview

The Application Binary Interface (ABI) defines the binary contract between the Runtime Core and every generated binding.

The ABI SHALL remain stable regardless of internal implementation changes.

The ABI SHALL become the only interface used by generated bindings.

The Runtime implementation MAY evolve without breaking the public SDK.

---

## Design Goals

The ABI SHALL provide:

- binary stability
- implementation independence
- language neutrality
- deterministic behavior
- minimal overhead
- forward compatibility
- backward compatibility whenever practical

---

## Architecture

```
              Runtime Core

                    │

             Internal Objects

                    │

         Internal Implementation

────────────────────────────────────

               ABI Layer

────────────────────────────────────

                    │

          Generated Bridge Layer

         ┌──────────┴──────────┐

         ▼                     ▼

    Kotlin SDK            Luau Runtime
```

Applications SHALL never communicate directly with Runtime internals.

---

## ABI Principles

The ABI SHALL expose only stable concepts.

The ABI SHALL NOT expose:

- C++ classes
- STL containers
- Lexbor types
- QuickJS types
- lonejson types
- MbedTLS types

Third-party implementations SHALL remain completely hidden.

---

## ABI Object Handle

Every native object SHALL be represented through an opaque handle.

Example object categories include:

- Runtime
- Module
- Document
- Element
- Elements
- JsonObject
- JsonArray
- Regex
- Pattern
- Match
- Buffer

Handles SHALL remain opaque.

Applications SHALL never inspect handle values.

---

## Handle Lifetime

Every handle SHALL belong to exactly one Runtime.

A handle SHALL become invalid immediately after object destruction.

Destroyed handles SHALL never be reused during the same Runtime lifetime.

---

## Handle Validation

Every ABI call SHALL validate:

- Runtime ownership
- handle validity
- object type
- object state

Invalid handles SHALL produce deterministic errors.

---

## Type Identifiers

Every public type SHALL expose a stable ABI Type Identifier.

Type identifiers SHALL:

- remain immutable
- remain unique
- remain language-independent

---

## Function Identifiers

Every exported function SHALL possess a stable identifier.

Generated bindings SHALL reference function identifiers instead of implementation details.

---

## Property Identifiers

Properties SHALL expose stable identifiers.

Property identifiers SHALL remain unchanged across compatible releases.

---

## Method Dispatch

Method invocation SHALL occur through generated dispatch tables.

Dispatch SHALL avoid string lookup whenever practical.

Runtime dispatch SHALL execute in constant time.

---

## ABI Calling Convention

Every ABI function SHALL define:

- parameter order
- return representation
- ownership semantics
- exception behavior

Calling conventions SHALL remain platform-independent whenever possible.

---

## Primitive Types

The ABI SHALL define canonical representations for:

- Boolean
- Integer
- Floating Point
- String
- Binary Buffer

Primitive representations SHALL remain deterministic.

---

## Object Types

Objects SHALL be passed exclusively through opaque handles.

Object memory SHALL never cross the ABI boundary directly.

---

## Collection Types

Collections SHALL expose stable collection handles.

Generated bindings SHALL provide language-specific wrappers.

The ABI SHALL remain collection-neutral.

---

## String Representation

The ABI SHALL define a canonical UTF-8 string representation.

Strings SHALL remain immutable.

Generated bindings MAY expose native language string types.

---

## Buffer Representation

Binary data SHALL be represented through immutable buffer descriptors.

Zero-copy transfer SHALL be preferred whenever practical.

---

## Error Representation

The ABI SHALL define a language-neutral error format.

Error descriptors SHALL include:

- identifier
- category
- message
- originating module

Generated bindings SHALL translate errors into language-specific exceptions.

---

## Exception Boundary

Exceptions SHALL NOT cross the ABI boundary directly.

The ABI SHALL return structured error information.

Language bindings SHALL reconstruct appropriate exception types.

---

## Ownership Contract

Every ABI function SHALL explicitly define:

- ownership retained
- ownership transferred
- borrowed reference
- shared reference

Ownership SHALL never be implicit.

---

## Lifetime Contract

Returned objects SHALL define explicit lifetime semantics.

Bindings SHALL never infer lifetime automatically.

---

## Reflection Access

Reflection SHALL be accessible through stable ABI interfaces.

Reflection SHALL expose descriptors instead of implementation objects.

---

## Version Negotiation

The Runtime SHALL expose:

- ABI version
- Runtime version
- Module versions

Generated bindings SHALL verify ABI compatibility during initialization.

---

## Feature Discovery

Bindings SHALL discover optional Runtime capabilities through the ABI.

Feature discovery SHALL avoid compile-time assumptions.

---

## Binary Compatibility

Minor Runtime releases SHOULD preserve ABI compatibility.

Breaking ABI changes SHALL require a new major ABI version.

---

## ABI Evolution

New ABI functionality SHALL be additive whenever practical.

Deprecated functions SHALL remain available until officially removed.

---

## Generated Bindings

All language bindings SHALL communicate exclusively through the ABI.

Handwritten ABI wrappers are prohibited.

---

## Performance Requirements

The ABI SHALL prioritize:

- constant-time dispatch
- minimal indirection
- minimal allocations
- zero-copy transfers
- stable handles
- cache-friendly layouts

---

## Security

The ABI SHALL validate every external request.

The Runtime SHALL never trust caller-provided handles without verification.

Invalid access SHALL fail safely.

---

## Thread Ownership

Every ABI object SHALL belong to one Runtime.

Cross-Runtime object usage SHALL be rejected.

---

## ABI Invariants

The ABI SHALL guarantee:

- opaque object handles
- stable type identifiers
- deterministic dispatch
- explicit ownership
- explicit lifetime
- implementation independence
- language neutrality
- generated bindings only
- stable binary contracts


