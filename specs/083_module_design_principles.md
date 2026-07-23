# Module Design Principles

Every module SHALL:

- expose one namespace
- expose one public API
- expose generated bindings
- expose generated documentation
- expose generated reflection
- expose generated tests

Modules SHALL NOT expose:

- native pointers
- implementation classes
- third-party APIs
- JNI
- internal allocators

---

