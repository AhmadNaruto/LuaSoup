# Luau Runtime

## Overview

The Luau Runtime is the scripting engine of the Native Runtime Platform.

The Runtime SHALL embed Luau as its primary scripting language.

Luau SHALL execute user scripts while all performance-critical operations remain implemented inside native modules.

The Luau Runtime SHALL remain completely isolated from platform-specific implementations.

---

## Design Goals

The Luau Runtime SHALL provide:

- fast startup
- predictable execution
- sandboxed environment
- native module integration
- deterministic behavior
- minimal memory overhead

---

## Runtime Ownership

Each Runtime SHALL own exactly one Luau VM.

A Luau VM SHALL belong to exactly one Runtime.

Sharing a Luau VM between Runtime instances is prohibited.

---

## VM Lifecycle

The VM SHALL follow the Runtime lifecycle.

```

Runtime Created

↓

Create Luau VM

↓

Register Core Modules

↓

Register Generated Bindings

↓

Execute Bootstrap

↓

Ready

↓

Running

↓

Shutdown

↓

Destroy VM

```

The VM SHALL be destroyed together with its owning Runtime.

---

## Bootstrap

During initialization the Runtime SHALL automatically register every enabled module.

Scripts SHALL NOT manually import built-in modules.

The bootstrap sequence SHALL remain deterministic.

---

## Global Namespace

Built-in modules SHALL be available through the global namespace.

Example modules include:

- html
- json
- regex
- crypto
- javascript
- url
- encoding
- buffer
- time
- util

The Runtime SHALL NOT require package loading for built-in modules.

---

## No require()

The Runtime SHALL NOT require:

- require()
- package.path
- package.cpath
- module loaders
- package managers

All built-in functionality SHALL be available immediately after Runtime initialization.

Third-party scripts MAY implement their own module systems independently.

---

## Module Registration

Module registration SHALL be fully automatic.

Registration SHALL be generated from the Meta Framework.

Handwritten registration code is prohibited.

---

## Generated Registration

The compiler SHALL generate:

- module registration
- userdata registration
- property registration
- method registration
- iterator registration
- constant registration
- enumeration registration

Runtime startup SHALL automatically execute generated registration.

---

## Native Userdata

Every native object SHALL be represented as userdata.

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

Userdata SHALL remain lightweight.

---

## Property Access

Properties SHALL behave like native Luau fields.

Example:

```lua
print(document.title)

print(element.text)

print(element.parent)
```

Property access SHALL remain transparent.

---

## Method Calls

Native methods SHALL behave exactly like ordinary Luau methods.

Example:

```lua
local links =
    document:select(".chapter")

local title =
    element:text()
```

No JNI concepts SHALL be exposed.

---

## Attribute Access

Dynamic attributes SHALL behave like ordinary properties.

Example:

```lua
print(element.id)

print(element.class)

print(element.href)
```

Unknown HTML attributes SHALL be resolved dynamically.

---

## Collection Objects

Native collections SHALL support:

- indexing
- iteration
- length
- property access

Collections SHALL feel identical to native Luau tables while remaining backed by native objects.

---

## Iteration

Collections SHALL support native iteration.

Example:

```lua
for _, element in ipairs(elements) do

end
```

Iteration SHALL avoid unnecessary allocations.

---

## Indexing

Collections SHALL support index access.

Example:

```lua
local first =
    elements[1]
```

Indexing SHALL execute in constant time whenever practical.

---

## Object Identity

Repeated access to the same native object SHOULD return the same userdata.

Identity SHALL remain stable.

Example:

```lua
assert(
    element.parent.children[1]
    == element
)
```

---

## Equality

Userdata SHALL distinguish:

- identity equality
- structural equality

Identity SHALL remain the default behavior.

---

## Automatic Type Conversion

The Runtime SHALL automatically convert:

Primitive values:

- nil
- boolean
- number
- string

Composite values:

- table
- array
- JSON

Native objects SHALL remain userdata.

---

## Deep Table Conversion

Nested Luau tables SHALL convert recursively.

Nested native objects SHALL preserve identity.

Circular references SHALL be detected automatically.

---

## JSON Integration

Native JSON SHALL integrate transparently with Luau tables.

Examples include:

- object
- array
- primitive values

Manual serialization SHOULD NOT be required.

---

## Error Handling

Native exceptions SHALL become ordinary Luau errors.

Error messages SHALL remain deterministic.

Native stack traces SHOULD be preserved whenever practical.

---

## Garbage Collection

Userdata SHALL participate in Luau garbage collection.

The Runtime SHALL synchronize:

- userdata lifetime
- native lifetime
- ownership

Garbage collection SHALL NOT produce resource leaks.

---

## Native Finalizers

Native objects MAY expose cleanup callbacks.

Cleanup SHALL occur automatically during userdata destruction.

Double destruction is prohibited.

---

## Reflection Support

Generated metadata SHALL register:

- class names
- properties
- methods
- constants
- enums

Reflection SHALL remain available internally.

---

## Sandbox

The Runtime SHALL execute inside a sandboxed environment.

Built-in modules SHALL expose only approved APIs.

Unsafe native functionality SHALL remain inaccessible.

---

## Runtime Isolation

Separate Runtime instances SHALL remain isolated.

Scripts SHALL NOT exchange userdata across Runtime boundaries.

Cross-runtime access SHALL fail safely.

---

## Performance Goals

The Luau Runtime SHALL prioritize:

- minimal allocations
- generated bindings
- property caching
- userdata reuse
- zero-copy conversion
- batched native execution
- deterministic startup

---

## Luau Runtime Invariants

The Runtime SHALL guarantee:

- exactly one Luau VM per Runtime
- automatically generated bindings
- no handwritten module registration
- no built-in require()
- stable userdata identity
- deterministic module initialization
- native ownership remains authoritative
- all built-in modules are immediately available


