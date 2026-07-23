# Deep Automatic Conversion

## Overview

The Bridge SHALL support recursive conversion of complex object graphs.

Nested objects SHALL be converted automatically.

No manual conversion SHALL be required.

---

## Collection Conversion

Collections SHALL preserve:

- ordering
- nesting
- nullability
- identity whenever possible

Supported collections include:

- List
- Array
- Map
- Set

---

## JSON Conversion

JSON SHALL become a first-class bridge type.

Native JSON objects SHALL automatically convert into:

- Kotlin collections
- Luau tables

Likewise:

- Kotlin collections
- Luau tables

SHALL automatically convert back into native JSON.

Manual serialization SHOULD NOT be required.

---

## Object Conversion

Native runtime objects SHALL remain native.

The Bridge SHALL expose lightweight wrappers.

Wrappers SHALL preserve object identity.

Objects SHALL NOT be duplicated unnecessarily.

---

## Identity Preservation

Every native object SHALL possess a unique Bridge Identifier.

Repeated conversion of the same native object SHALL return the same wrapper whenever practical.

Example:

```
Document

↓

Element

↓

Bridge

↓

Kotlin Element
```

Repeated requests SHALL reuse the same wrapper.

---

## Wrapper Cache

The Bridge SHALL maintain wrapper caches.

Separate caches SHALL exist for:

- Kotlin wrappers
- Luau userdata

Wrapper reuse SHALL reduce allocations.

---

## Circular References

Circular object graphs SHALL be supported.

The Bridge SHALL detect cycles automatically.

Infinite recursion during conversion is prohibited.

---

## Shared References

Shared references SHALL remain shared.

Example:

```
A

↓

B

↑

C
```

The converted graph SHALL preserve sharing.

---

## Nullability

Null values SHALL remain null.

Implicit conversion between null and empty collections is prohibited.

---

## Ownership Transfer

Ownership SHALL remain explicit.

Supported modes include:

- Shared
- Borrowed
- Unique

Ownership SHALL influence wrapper lifetime.

---

## Lifetime Synchronization

Wrapper lifetime SHALL remain synchronized with native lifetime.

Destroyed native objects SHALL invalidate all wrappers.

Invalid wrappers SHALL fail safely.

---

## Lazy Conversion

Complex objects SHOULD be converted lazily.

Expensive child objects SHALL NOT be converted until accessed.

---

## Property Access

Property reads SHOULD occur lazily.

Example:

```
document.title
```

SHALL retrieve only the title.

The Bridge SHALL NOT eagerly load unrelated properties.

---

## Collection Views

Native collections SHOULD expose lightweight views.

Views SHALL support:

- iteration
- indexing
- size
- lazy element conversion

---

## Batch Conversion

The Bridge SHOULD support batched conversions.

Large collections SHOULD minimize JNI transitions.

---

## Buffer Mapping

Byte buffers SHALL support zero-copy mapping whenever practical.

Copies SHALL occur only when required for safety.

---

## Exception Translation

Native exceptions SHALL become language-specific exceptions.

Examples:

Native Exception

↓

Kotlin Exception

↓

Luau Error

Exception messages SHALL remain consistent.

---

## Thread Safety

Bridge objects SHALL belong to exactly one Runtime.

Bridge objects SHALL NOT migrate between Runtime instances.

Thread ownership SHALL remain explicit.

---

## Bridge Cache

The Bridge SHALL maintain caches for:

- wrappers
- strings
- arrays
- reflection lookups
- converters

Caches SHALL belong to one Runtime.

---

## Reflection Integration

The Bridge SHALL use Reflection metadata.

Type conversion SHALL NOT depend on handwritten mappings.

Reflection SHALL describe:

- properties
- methods
- ownership
- nullability
- collections

---

## Generated Bindings

The Bridge SHALL rely exclusively on generated bindings.

Handwritten bridge code SHOULD be minimized.

Generated bindings SHALL remain deterministic.

---

## Performance Goals

The Native Bridge Engine SHALL prioritize:

- zero-copy
- wrapper reuse
- identity preservation
- lazy conversion
- batched JNI calls
- minimal allocations
- minimal JNI transitions

---

## Native Bridge Invariants

The Bridge SHALL guarantee:

- every wrapper belongs to one Runtime
- every wrapper represents exactly one native object
- wrapper identity remains stable
- ownership never becomes ambiguous
- circular references remain valid
- temporary bridge allocations are released automatically
- generated bindings remain the single source of bridge behavior


