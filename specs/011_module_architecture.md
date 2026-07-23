# Module Architecture

## Overview

Modules are the functional building blocks of the Native Runtime Platform.

Every capability exposed by the Runtime SHALL belong to exactly one module.

Modules SHALL remain isolated, independently maintainable, and implementation-independent.

Public APIs SHALL remain stable regardless of internal implementation changes.

---

## Design Goals

The Module Architecture SHALL provide:

- clear separation of responsibilities
- strong encapsulation
- deterministic initialization
- automatic registration
- implementation independence
- consistent public APIs

---

## Module Categories

Modules SHALL be classified into one of the following categories.

### Core Modules

Core Modules are always available.

Examples include:

- html
- json
- regex
- crypto
- url
- encoding
- buffer
- util
- time

Core Modules SHALL initialize automatically.

---

### Optional Modules

Optional Modules may be disabled during build.

Examples include:

- javascript
- xml
- sqlite
- compression

Disabled modules SHALL contribute no runtime overhead.

---

### Platform Modules

Platform Modules expose platform-specific functionality.

Examples include:

- android
- filesystem
- preferences
- logging

Platform Modules SHALL communicate through Kotlin.

They SHALL NOT access Android APIs directly from native code unless explicitly required.

---

## Module Structure

Every module SHALL follow the same internal structure.

```

Module

├── Metadata
├── Public API
├── Native Implementation
├── Reflection Descriptor
├── Tests
├── Benchmarks
└── Documentation

```

---

## Module Descriptor

Every module SHALL define:

- identifier
- namespace
- version
- dependencies
- capabilities
- exported classes
- exported constants
- exported enumerations

The descriptor SHALL be generated into Reflection.

---

## Namespace

Each module SHALL own exactly one namespace.

Example:

```

html

json

regex

crypto

```

Namespace collisions are prohibited.

---

## Public API

The Public API SHALL expose only stable interfaces.

Implementation details MUST remain hidden.

Native libraries SHALL NOT leak into the API surface.

---

## Internal Implementation

Modules MAY use any internal implementation.

Examples include:

- Lexbor
- lonejson
- lua-std-regex
- Mbed TLS
- QuickJS-NG

Replacing an implementation SHALL NOT affect the Public API.

---

## Dependency Rules

Modules SHALL communicate only through public Runtime services.

Modules SHALL NOT directly access the internal implementation of another module.

The following dependencies are permitted:

```

Module

↓

Runtime Services

↓

Other Module

```

Direct module-to-module coupling is prohibited.

---

## Module Lifecycle

Each module SHALL progress through the following lifecycle.

```

Discovered

↓

Registered

↓

Initialized

↓

Ready

↓

Running

↓

Stopping

↓

Released

```

Lifecycle transitions SHALL be deterministic.

---

## Module Initialization

Initialization SHALL occur in dependency order.

A module SHALL initialize only after all required dependencies become available.

---

## Module Shutdown

Shutdown SHALL occur in reverse dependency order.

Modules SHALL release all resources before returning control to the Runtime.

---

## Capabilities

Each module SHALL declare its capabilities.

Example:

```

html.parser

html.selector

html.dsl

json.decoder

regex.compiler

crypto.aes

crypto.hash

```

Capabilities SHALL be discoverable through Reflection.

---

## Reflection Registration

Every module SHALL automatically register:

- classes
- methods
- properties
- constants
- enums
- documentation

Registration SHALL be generated.

Manual registration is prohibited.

---

## Generated Bindings

Every module SHALL automatically generate:

- Kotlin bindings
- Luau bindings
- JNI bindings
- Documentation
- Tests

Modules SHALL never maintain handwritten public bindings.

---

## Native Resources

Every module SHALL own its native resources.

Resources SHALL be released during module shutdown.

Resources SHALL NOT outlive the Runtime.

---

## Configuration

Modules MAY expose immutable configuration.

Configuration SHALL be supplied during Runtime creation.

Configuration SHALL become read-only after initialization.

---

## Error Handling

Every module SHALL expose deterministic error behavior.

Errors SHALL be translated into:

- Kotlin Exceptions
- Luau Errors

Native implementation details SHALL remain hidden.

---

## Performance Policy

Modules SHALL prioritize:

- zero-copy operations
- lazy evaluation
- object reuse
- arena allocation
- cache locality
- batched execution

---

## Thread Safety

Modules SHALL inherit the Runtime threading model.

Modules SHALL NOT introduce independent synchronization mechanisms.

---

## Memory Ownership

Modules SHALL never own memory outside the Runtime.

All allocations SHALL originate from the Runtime Memory Manager.

---

## Cache Integration

Modules SHALL use the centralized Cache Manager.

Modules SHALL NOT implement independent cache systems.

Supported cache categories include:

- Selector Cache
- Regex Cache
- Execution Cache
- Reflection Cache
- String Cache

---

## Logging

Modules SHALL emit structured diagnostic events.

Logging SHALL remain optional.

Production builds SHOULD disable verbose diagnostics.

---

## Testing

Every module SHALL provide:

- unit tests
- integration tests
- benchmark tests
- metadata validation

Generated APIs SHALL be validated automatically.

---

## Documentation

Documentation SHALL originate from metadata.

Manual duplication of API documentation is prohibited.

---

## Binary Compatibility

Module updates SHOULD preserve binary compatibility whenever practical.

Breaking changes SHALL require version increments.

---

## Future Extensibility

New modules SHALL integrate without requiring modifications to:

- Runtime Core
- Bridge Engine
- Kotlin SDK
- Luau Runtime
- Existing Modules

The Runtime SHALL discover new modules automatically through generated metadata.

---

## Module Invariants

The Module Architecture SHALL guarantee:

- one namespace per module
- deterministic initialization
- deterministic shutdown
- generated public bindings
- generated reflection
- centralized memory management
- centralized cache management
- implementation-independent public APIs
- automatic Runtime registration

