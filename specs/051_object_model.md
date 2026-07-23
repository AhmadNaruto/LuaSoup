# Object Model

## Overview

The Object Model defines the behavior of every public object exposed by the Native Runtime Platform.

Every module SHALL follow exactly the same object semantics.

Regardless of whether an object originates from:

- HTML
- JSON
- Regex
- JavaScript
- Crypto
- URL
- Encoding

it SHALL behave identically.

The Object Model SHALL become one of the fundamental contracts of the Runtime.

---

## Design Goals

The Object Model SHALL provide:

- consistent APIs
- predictable behavior
- stable identity
- reflection compatibility
- language independence
- deterministic lifetime

Applications SHALL never need to learn different object semantics for different modules.

---

