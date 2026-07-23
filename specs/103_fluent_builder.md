# Fluent Builder

Every DSL SHALL use a fluent builder style.

Example:

```
html.query {

    select(".chapter")

    first()

    text()
}
```

The same semantics SHALL exist in Luau.

---

