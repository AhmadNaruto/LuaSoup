# Toolchain Invariants

The Compiler Toolchain SHALL guarantee:

- metadata is the only editable source
- IR is the only backend input
- generated artifacts are deterministic
- handwritten bindings are prohibited
- handwritten reflection is prohibited
- handwritten documentation is prohibited
- compiler output is reproducible
- backend implementations remain independent

