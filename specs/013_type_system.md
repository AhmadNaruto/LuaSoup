# Type System

## Overview

The Type System defines every data type supported by the Native Runtime Platform.

The Type System SHALL provide a unified representation across:

- Runtime
- Kotlin
- Luau
- Reflection
- Compiler
- Bridge Engine

Every public value SHALL be represented by a well-defined type descriptor.

---

## Design Goals

The Type System SHALL provide:

- deterministic behavior
- strong typing
- explicit nullability
- platform independence
- reflection support
- automatic conversions
- stable ABI

The Type System SHALL become the foundation of every generated binding.

---

## Type Categories

The Runtime SHALL support the following type categories.

### Primitive Types

- Boolean
- Int8
- UInt8
- Int16
- UInt16
- Int32
- UInt32
- Int64
- UInt64
- Float32
- Float64
- Char
- String
- Binary

Primitive types SHALL be immutable.

---

## Object Types

Object types SHALL represent native runtime objects.

Examples include:

- Document
- Element
- Elements
- JsonObject
- JsonArray
- Regex
- Pattern
- Match
- Url
- Buffer

Object identity SHALL remain stable.

---

## Value Types

Value Types SHALL behave as immutable values.

Examples include:

- Version
- Color
- Point
- Rect
- Size
- Duration

Value Types SHOULD be passed by value whenever practical.

---

## Reference Types

Reference Types SHALL represent shared native resources.

Reference Types SHALL preserve:

- identity
- ownership
- lifetime

Reference Types SHALL NOT be copied implicitly.

---

## Nullable Types

Nullability SHALL be explicit.

Every reference SHALL declare either:

- Nullable
- NonNull

Implicit nullable behavior is prohibited.

---

## Collection Types

The Runtime SHALL support:

- Array
- List
- Set
- Map
- Queue
- Stack

Collections SHALL preserve element types.

---

## Generic Types

Generic Types SHALL be fully supported.

Examples include:

- Array<Element>
- List<Document>
- Map<String, String>
- Set<Node>

Generic metadata SHALL remain available in Reflection.

---

## Function Types

Function Types SHALL support:

- parameters
- return type
- ownership
- exceptions

Callbacks SHALL be represented using Function Types.

---

## Iterator Types

Collection objects SHALL expose iterator descriptors.

Iterators SHALL support:

- sequential traversal
- lazy traversal
- bidirectional traversal when supported

---

## Optional Types

Optional values SHALL be represented explicitly.

Optional SHALL remain distinct from nullable references.

---

## Union Types

Future Runtime versions MAY support union types.

Example:

```
String | Number
```

The Type System SHALL remain extensible.

---

## Enumeration Types

Enumerations SHALL define:

- identifier
- values
- integer representation
- documentation

Enumerations SHALL remain immutable.

---

## Flag Types

Flags SHALL represent bit-mask values.

Generated bindings SHALL expose idiomatic flag APIs.

---

## Alias Types

Alias Types SHALL define semantic names for existing types.

Aliases SHALL preserve underlying ABI compatibility.

---

## Type Identity

Every Type SHALL have:

- unique identifier
- qualified name
- namespace
- category

Type identifiers SHALL remain stable.

---

## Type Resolution

Type resolution SHALL occur during compilation.

Backends SHALL receive fully resolved type information.

---

## Type Conversion

The Bridge Engine SHALL automatically convert compatible types.

Implicit conversions SHALL be limited to safe conversions.

Unsafe conversions are prohibited.

---

## Type Compatibility

Two types SHALL be considered compatible only when explicitly defined.

Compatibility SHALL remain deterministic.

---

## Runtime Type Information

Every object SHALL expose Runtime Type Information (RTTI).

RTTI SHALL support:

- exact type lookup
- inheritance lookup
- interface lookup

RTTI SHALL remain allocation-free whenever practical.

---

## Type Registry

Every Runtime SHALL own one Type Registry.

The Type Registry SHALL contain:

- primitive types
- object types
- collection types
- generic instantiations
- aliases

The registry SHALL become immutable after initialization.

---

## Type Lookup

Type lookup SHALL support:

- identifier
- qualified name
- namespace
- category

Lookup SHOULD execute in constant time.

---

## Type Serialization

Every public type SHALL define serialization metadata.

Serialization SHALL remain independent from implementation.

---

## ABI Representation

Every Type SHALL define an ABI representation.

ABI descriptors SHALL remain stable across compiler versions.

---

## Reflection Integration

Every Type SHALL automatically generate Reflection metadata.

Reflection SHALL become the authoritative runtime representation of all types.

---

## Kotlin Mapping

Every Type SHALL define its Kotlin representation.

Mappings SHALL be generated automatically.

Manual mapping is prohibited.

---

## Luau Mapping

Every Type SHALL define its Luau representation.

Generated userdata SHALL preserve native semantics.

---

## JSON Mapping

Supported Types SHALL define JSON conversion rules.

JSON conversion SHALL be automatic whenever practical.

---

## Type Validation

Compilation SHALL validate:

- duplicate types
- invalid inheritance
- invalid generic usage
- recursive definitions
- incompatible overrides

Compilation SHALL fail on validation errors.

---

## Future Compatibility

The Type System SHALL allow future type categories without breaking existing metadata.

Unknown types SHALL be ignored safely by older compiler versions whenever practical.

---

## Type System Invariants

The Type System SHALL guarantee:

- every public type has one descriptor
- type identifiers remain stable
- nullability is explicit
- generic information is preserved
- ABI representation is deterministic
- Reflection remains synchronized
- generated bindings use the same type definitions
- all language bindings originate from the same Type System

