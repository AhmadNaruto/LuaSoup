# Standard Module Layout

Every module SHALL follow the same internal organization.

```
module/

├── meta/
│   ├── module.kt
│   ├── classes.kt
│   ├── enums.kt
│   ├── constants.kt
│   └── documentation.kt
│
├── native/
│   ├── include/
│   ├── source/
│   └── implementation/
│
├── generated/
│
├── tests/
│
├── benchmark/
│
└── docs/
```

The layout SHALL remain consistent across every module.

---

