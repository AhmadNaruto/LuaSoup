package com.luasoup.crypto

/**
 * AES Cipher Modes specified in specs/090_crypto_module.md
 */
enum class AesMode {
    ECB,
    CBC,
    CTR,
    GCM
}

/**
 * AES Padding Schemes specified in specs/090_crypto_module.md
 */
enum class AesPadding {
    PKCS7,
    NoPadding
}
