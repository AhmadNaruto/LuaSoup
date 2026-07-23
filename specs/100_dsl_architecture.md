# DSL Architecture

```
Application

        │

        ▼

    Kotlin DSL
      Luau DSL

        │

        ▼

 DSL Builder Layer

        │

        ▼

 Intermediate DSL Tree

        │

        ▼

 DSL Optimizer

        │

        ▼

 Execution Plan

        │

        ▼

 Native Runtime
```

The DSL SHALL never execute directly from the Builder.

---

