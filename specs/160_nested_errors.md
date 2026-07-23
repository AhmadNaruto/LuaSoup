# Nested Errors

Errors MAY contain a cause.

Nested causes SHALL preserve the original error chain.

Example:

```
Runtime Error

↓

HTML Error

↓

Lexbor Error
```

Only Runtime-visible errors SHALL reach applications.

---

