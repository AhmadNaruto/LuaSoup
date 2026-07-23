# Chainable APIs

Methods MAY return the current object to enable chaining.

Example:

```
document
    .select(...)
    .first()
    .text()
```

Generated bindings SHALL preserve fluent APIs.

---

