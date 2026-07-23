# Exception Translation

Errors SHALL automatically translate into language-specific representations.

Kotlin:

```
RuntimeException

IllegalArgumentException

IllegalStateException

IOException
```

Luau:

```lua
error(...)
```

Applications SHALL never receive native exceptions.

---

