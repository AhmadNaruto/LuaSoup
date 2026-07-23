# Conversion Service

## Overview

The Conversion Service SHALL perform automatic type conversion.

Supported conversions include:

- Kotlin ↔ Native
- Luau ↔ Native
- JSON ↔ Native
- Table ↔ JSON
- Collection ↔ Native

Manual conversion SHOULD NOT be required.

---

## Deep Conversion

Nested object graphs SHALL be converted automatically.

Circular references SHALL be preserved.

Identity SHALL remain stable.

---

