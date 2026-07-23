# Runtime Core

## Overview

The Runtime Core is the execution engine of the Native Runtime Platform.

It owns every runtime resource and coordinates all native modules.

The Runtime Core SHALL remain independent from:

- Android
- Kotlin
- JNI
- Luau standard libraries
- Third-party frameworks

Every native module SHALL execute under exactly one Runtime instance.

---

## Responsibilities

The Runtime Core SHALL be responsible for:

- Runtime lifecycle
- Module lifecycle
- Memory management
- Object ownership
- Reflection database
- Type registry
- Module registry
- Cache management
- Error propagation
- Scheduler
- Native resource tracking
- Runtime configuration

---

## Runtime Instance

A Runtime instance SHALL represent a completely isolated execution environment.

Each Runtime SHALL own:

- Luau VM
- Reflection Database
- Module Registry
- Type Registry
- Cache Manager
- Memory Manager
- Scheduler
- Native Handle Manager

Objects MUST NOT be shared between Runtime instances unless explicitly supported.

---

## Runtime Lifecycle

The Runtime SHALL progress through the following states.

```
Created

↓

Initializing

↓

Registering Modules

↓

Building Reflection

↓

Ready

↓

Running

↓

Stopping

↓

Disposed
```

Transitions SHALL be deterministic.

---

## Runtime Initialization

Initialization SHALL execute in the following order.

```
Create Runtime

↓

Initialize Memory Manager

↓

Initialize Reflection Database

↓

Initialize Type Registry

↓

Initialize Cache Manager

↓

Register Core Modules

↓

Register Optional Modules

↓

Finalize Reflection

↓

Freeze Metadata

↓

Ready
```

No public API SHALL be accessible before initialization completes.

---

## Runtime Configuration

The Runtime SHALL support immutable startup configuration.

Configuration MAY include:

- cache limits
- module enablement
- debug mode
- profiling
- allocator selection
- validation level

Configuration SHALL become read-only after initialization.

---

## Runtime Context

Every execution SHALL receive a Runtime Context.

The Runtime Context SHALL expose:

- current runtime
- current VM
- current allocator
- current scheduler
- current cache manager
- current exception handler

The Runtime Context SHALL remain internal.

---

## Module Registry

The Runtime SHALL maintain a centralized Module Registry.

The registry SHALL contain:

- module identifier
- namespace
- version
- dependencies
- capabilities
- initialization state

Modules SHALL register automatically during startup.

---

## Type Registry

Every public runtime type SHALL be registered.

Examples include:

- Document
- Element
- Elements
- JsonObject
- JsonArray
- Regex
- Pattern
- Match
- Buffer
- Url

Each type SHALL receive a unique runtime identifier.

---

## Reflection Database

The Reflection Database SHALL be constructed during initialization.

The database SHALL contain:

- modules
- classes
- interfaces
- methods
- properties
- constants
- enumerations
- documentation metadata

Reflection SHALL become immutable after initialization.

---

## Runtime Scheduler

The Runtime SHALL own an internal scheduler.

The scheduler SHALL coordinate:

- asynchronous callbacks
- deferred cleanup
- background compilation
- cache maintenance

The scheduler SHALL remain platform-independent.

---

## Native Handle Manager

Every native object SHALL receive an internal handle.

Handles SHALL:

- remain unique
- remain opaque
- never expose native pointers
- support validation

Handles SHALL be invalidated immediately after object destruction.

---

## Object Identity

Every public object SHALL possess stable identity.

Identity SHALL remain valid until object destruction.

Identity SHALL NOT depend on memory addresses.

Equality SHALL distinguish between:

- identity equality
- structural equality

Each type MAY define structural equality independently.

---

## Object Ownership

Ownership SHALL be tracked by the Runtime.

Supported ownership kinds include:

- Shared
- Borrowed
- Unique
- Weak

Ownership transfer SHALL remain explicit.

Implicit ownership transfer is prohibited.

---

## Lifetime Tracking

Every native object SHALL be tracked.

The Runtime SHALL know:

- creator
- owner
- reference count (if applicable)
- destruction policy
- current state

Destroyed objects SHALL immediately become invalid.

---

## Resource Manager

The Runtime SHALL own every native resource.

Examples include:

- DOM trees
- JSON trees
- Regex objects
- JavaScript contexts
- Buffers
- Cryptographic contexts

Resource cleanup SHALL be automatic.

---

## Module Capabilities

Modules SHALL declare capabilities.

Examples:

- html.parser
- html.selector
- html.dsl
- json.decoder
- regex.compiler
- crypto.hash

Capabilities SHALL be discoverable through Reflection.

---

## Feature Flags

Optional runtime functionality SHALL be represented using feature flags.

Examples include:

- JavaScript
- Crypto
- Regex
- HTML

Disabled modules SHALL consume no runtime resources.

---

## Thread Model

A Runtime instance SHALL be single-threaded unless explicitly configured otherwise.

Native objects SHALL NOT be accessed concurrently without synchronization.

Future multi-threaded runtimes SHALL preserve API compatibility.

---

## Runtime Isolation

Runtime instances SHALL remain completely isolated.

Isolation SHALL include:

- object graphs
- caches
- reflection
- allocators
- schedulers

Cross-runtime object access is prohibited.

---

## Freeze Phase

After initialization completes:

- Reflection SHALL become immutable.
- Metadata SHALL become immutable.
- Module registration SHALL be locked.
- Type registration SHALL be locked.

This guarantees deterministic execution.

---

## Runtime Shutdown

Shutdown SHALL execute in reverse initialization order.

```
Stop Scheduler

↓

Flush Pending Tasks

↓

Release Modules

↓

Release Reflection

↓

Release Registries

↓

Release Memory

↓

Destroy VM
```

Every resource SHALL be released exactly once.

---

## Error Recovery

Initialization failures SHALL trigger complete rollback.

Partially initialized runtimes SHALL NOT remain usable.

Resource leaks during startup are prohibited.

---

## Runtime Invariants

The Runtime SHALL guarantee:

- Reflection never changes after startup.
- Every public type has exactly one descriptor.
- Every object belongs to one Runtime.
- Every module has exactly one namespace.
- Every native handle is unique.
- Every cache belongs to one Runtime.

These invariants SHALL remain true throughout the lifetime of the Runtime.

