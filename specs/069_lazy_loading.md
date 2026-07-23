# Lazy Loading

Expensive properties SHOULD be loaded lazily.

Example:

```
document.body

element.children

json.largeArray
```

Lazy loading SHALL avoid unnecessary allocations.

---

