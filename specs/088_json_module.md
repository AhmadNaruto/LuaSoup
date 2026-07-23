# JSON Module

## Overview

The JSON Module SHALL use lonejson.

lonejson SHALL remain completely hidden.

The JSON Module SHALL expose:

- JsonObject
- JsonArray
- JsonValue

---

## Automatic Conversion

Native JSON SHALL automatically convert to:

- Kotlin collections
- Luau tables

Likewise:

- Kotlin collections
- Luau tables

SHALL convert back into native JSON automatically.

---

## Deep Conversion

Nested JSON SHALL support recursive conversion.

Object identity SHALL remain preserved whenever applicable.

---

