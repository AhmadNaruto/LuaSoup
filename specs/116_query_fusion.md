# Query Fusion

Adjacent compatible operations SHOULD be fused.

Example:

```
select()

↓

first()

↓

text()
```

SHALL become a single execution pipeline whenever practical.

---

