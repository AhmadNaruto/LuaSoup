# Crypto Module

## Overview

The Crypto Module SHALL use Mbed TLS.

OpenSSL SHALL NOT be included.

---

## Supported Algorithms

The Crypto Module SHALL provide:

### Hash

- MD5
- SHA-1
- SHA-224
- SHA-256
- SHA-384
- SHA-512

### HMAC

- HMAC-SHA1
- HMAC-SHA256
- HMAC-SHA512

### AES

The Runtime SHALL support:

- AES-128
- AES-192
- AES-256

Supported modes include:

- ECB
- CBC
- CTR
- GCM

Padding SHALL support:

- PKCS7
- NoPadding

---

## Random Generator

The Runtime SHALL expose secure random generation.

Random generation SHALL rely on Mbed TLS.

---

