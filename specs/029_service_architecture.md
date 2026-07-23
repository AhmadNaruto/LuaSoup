# Service Architecture

```
                    Runtime

                       │

        ┌──────────────┼──────────────┐

        ▼              ▼              ▼

   Memory Service   Cache Service   Type Service

        ▼              ▼              ▼

 Reflection      Event Service   Task Scheduler

        ▼              ▼              ▼

  Bridge Service   Module Service  Configuration

                       │

                    Modules
```

Every service SHALL be initialized by the Runtime.

---

