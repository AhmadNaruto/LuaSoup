# Regex Module

## Overview

The Regex Module SHALL use lua-std-regex.

The Runtime SHALL expose regex functionality without exposing the underlying implementation.

---

## Responsibilities

The Regex Module SHALL support:

- compile
- match
- search
- replace
- split
- captures

Compiled regex SHALL be cached automatically.

---

