# Luau DSL

Generated Luau DSL SHALL preserve identical semantics.

Example:

```lua
html.query(function(q)

    q:select(".chapter")

    q:first()

    q:text()

end)
```

The Runtime SHALL generate Luau DSL automatically.

---

