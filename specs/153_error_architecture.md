# Error Architecture

```
Native Library

        │

        ▼

Module Error

        │

        ▼

Runtime Error

        │

        ▼

Bridge Translation

        │

   ┌────┴────┐

   ▼         ▼

 Kotlin    Luau
Exception   Error
```

Native implementation details SHALL remain hidden.

---

