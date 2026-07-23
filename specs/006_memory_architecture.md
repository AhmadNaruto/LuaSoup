# Memory Architecture

## Overview

The Memory Architecture defines how the Native Runtime Platform allocates, owns, tracks, shares, and releases native memory.

Memory management SHALL remain completely transparent to both Luau and Kotlin.

Applications SHALL never manipulate native memory directly.

The Runtime SHALL remain the sole owner of all native allocations.

---

## Design Goals

The Memory Architecture SHALL provide:

- deterministic ownership
- minimal allocations
- predictable lifetime
- zero memory leaks
- high locality
- low fragmentation
- fast allocation
- automatic cleanup

---

## Memory Domains

The Runtime SHALL organize memory into independent domains.

Supported domains include:

- Runtime Memory
- VM Memory
- Module Memory
- Temporary Memory
- Cache Memory
- External Memory

Memory SHALL NOT be shared across domains unless explicitly permitted.

---

## Runtime Allocator

Every Runtime SHALL own a dedicated allocator.

The Runtime Allocator SHALL become the parent allocator for every native module.

All native allocations SHALL originate from the Runtime Allocator.

Direct use of malloc(), calloc(), realloc(), or free() inside modules is prohibited.

Modules SHALL allocate memory exclusively through the Runtime allocation API.

---

## Arena Allocation

Temporary allocations SHOULD use Arena Allocators.

Arena Allocators SHALL support:

- sequential allocation
- bulk release
- constant-time reset
- minimal fragmentation

Arena allocation SHALL be preferred for:

- HTML parsing
- JSON parsing
- Selector execution
- DSL execution
- Temporary buffers

---

## Object Allocation

Long-lived objects SHALL be allocated separately from temporary arenas.

Examples include:

- Document
- Element
- JsonObject
- Regex
- JavaScript Runtime

These objects SHALL remain valid until explicitly released by the Runtime.

---

## Stack Allocation

Whenever practical, short-lived objects SHOULD be allocated on the stack.

Heap allocation SHALL be avoided for small temporary values.

---

## String Allocation

Strings SHALL use a dedicated String Manager.

The String Manager SHALL support:

- UTF-8 storage
- deduplication
- immutable strings
- shared references

Duplicate immutable strings SHOULD reuse existing storage.

---

## Buffer Allocation

Binary buffers SHALL be allocated through the Buffer Manager.

The Buffer Manager SHALL support:

- contiguous allocation
- slicing
- shared views
- copy-on-write
- zero-copy mapping

---

## Object Pool

Frequently allocated objects SHOULD use object pools.

Examples include:

- iterator objects
- selector execution state
- temporary vectors
- token objects
- parser nodes

Pools SHALL minimize heap allocation.

---

## Cache Allocation

Caches SHALL own independent memory pools.

Examples:

- Selector Cache
- Regex Cache
- String Cache
- Reflection Cache
- Execution Plan Cache

Cache memory SHALL remain isolated from runtime object memory.

---

## Lifetime Categories

Every allocation SHALL belong to one lifetime category.

Supported categories include:

- Permanent
- Runtime
- Session
- Request
- Temporary
- Stack

Lifetime SHALL determine destruction policy.

---

## Ownership Tracking

Every allocation SHALL have exactly one owner.

Ownership SHALL be tracked internally.

Supported ownership kinds include:

- Unique
- Shared
- Borrowed
- Weak

Ownership SHALL never become ambiguous.

---

## Reference Tracking

The Runtime SHALL track references between native objects.

Reference tracking SHALL support:

- shared ownership
- borrowed references
- weak references
- circular reference detection

Reference graphs SHALL remain internal.

---

## Circular References

Circular references SHALL be detected whenever applicable.

The Runtime SHALL ensure circular ownership cannot produce memory leaks.

---

## Weak References

Weak references SHALL never prevent object destruction.

Accessing expired weak references SHALL safely return null.

---

## Object Destruction

Object destruction SHALL occur exactly once.

Destruction SHALL release:

- native memory
- caches
- handles
- external resources

Double destruction is prohibited.

---

## Deferred Destruction

The Runtime MAY defer destruction when immediate destruction is unsafe.

Deferred destruction SHALL execute through the Runtime Scheduler.

---

## Resource Finalization

Every native resource SHALL define a finalization procedure.

Finalization SHALL remain deterministic.

Finalizers MUST NOT allocate unnecessary memory.

---

## Memory Safety

The Runtime SHALL protect against:

- double free
- use-after-free
- dangling pointers
- invalid ownership transfer
- invalid handle access
- memory corruption

Safety checks MAY be disabled in optimized production builds.

---

## Zero-Copy Policy

Whenever practical, data SHALL remain in native memory.

Copies SHOULD be avoided.

Zero-copy SHALL be preferred for:

- ByteArray mapping
- Buffer views
- JSON serialization
- HTML extraction
- Kotlin bridge

---

## Copy-on-Write

Shared mutable data SHOULD use Copy-on-Write semantics.

Copy-on-Write SHALL occur only when mutation becomes necessary.

---

## Allocation Statistics

The Runtime SHALL collect allocation statistics.

Statistics MAY include:

- allocation count
- allocation size
- active allocations
- peak allocations
- cache usage
- fragmentation

Statistics SHALL support profiling.

---

## Leak Detection

Debug builds SHALL support automatic leak detection.

Leak reports SHOULD identify:

- object type
- allocation site
- owner
- lifetime
- remaining references

Leak detection SHALL remain optional in production builds.

---

## Memory Limits

The Runtime MAY define configurable limits.

Examples include:

- maximum cache size
- maximum DOM size
- maximum JSON size
- maximum buffer size

Exceeding limits SHALL produce deterministic errors.

---

## Memory Pressure

The Runtime SHALL respond to memory pressure.

Possible actions include:

- cache eviction
- pool shrinking
- temporary arena reset
- deferred cleanup

Applications SHALL remain operational whenever practical.

---

## Deterministic Cleanup

Destroying a Runtime SHALL release every allocation owned by that Runtime.

After Runtime destruction:

- every native handle becomes invalid
- every cache is released
- every arena is destroyed
- every object pool is released
- every native object is destroyed

No allocation SHALL survive Runtime destruction.

---

## Memory Invariants

The Memory Architecture SHALL guarantee:

- every allocation has exactly one owner
- every object belongs to one Runtime
- every allocation belongs to one memory domain
- every object is destroyed exactly once
- every handle becomes invalid after destruction
- every arena reset releases all temporary allocations
- no native memory survives Runtime shutdown


