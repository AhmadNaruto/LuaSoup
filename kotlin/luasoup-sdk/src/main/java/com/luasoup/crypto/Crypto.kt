package com.luasoup.crypto

import java.security.MessageDigest
import java.security.SecureRandom
import javax.crypto.Cipher
import javax.crypto.Mac
import javax.crypto.spec.IvParameterSpec
import javax.crypto.spec.SecretKeySpec

/**
 * Crypto Module according to specs/090_crypto_module.md (Mbed TLS / Native Crypto)
 * Supports: MD5, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512, HMAC, AES-128/192/256 (ECB, CBC, CTR, GCM), Secure Random
 */
object Crypto {

    @JvmStatic fun md5(data: String): String = hash("MD5", data)
    @JvmStatic fun sha1(data: String): String = hash("SHA-1", data)
    @JvmStatic fun sha224(data: String): String = hash("SHA-224", data)
    @JvmStatic fun sha256(data: String): String = hash("SHA-256", data)
    @JvmStatic fun sha384(data: String): String = hash("SHA-384", data)
    @JvmStatic fun sha512(data: String): String = hash("SHA-512", data)

    @JvmStatic
    fun hmacSha1(key: String, data: String): String = hmac("HmacSHA1", key, data)

    @JvmStatic
    fun hmacSha256(key: String, data: String): String = hmac("HmacSHA256", key, data)

    @JvmStatic
    fun hmacSha512(key: String, data: String): String = hmac("HmacSHA512", key, data)

    /**
     * AES Encryption (AES-128, AES-192, AES-256 with ECB/CBC/CTR/GCM modes and PKCS7/NoPadding)
     */
    @JvmStatic
    fun aesEncrypt(
        key: ByteArray,
        iv: ByteArray,
        data: ByteArray,
        mode: AesMode = AesMode.CBC,
        padding: AesPadding = AesPadding.PKCS7
    ): ByteArray {
        val cipherMode = mode.name
        val paddingScheme = if (padding == AesPadding.PKCS7) "PKCS5Padding" else "NoPadding"
        val cipher = Cipher.getInstance("AES/$cipherMode/$paddingScheme")
        val secretKey = SecretKeySpec(key, "AES")

        if (mode == AesMode.ECB) {
            cipher.init(Cipher.ENCRYPT_MODE, secretKey)
        } else {
            val ivSpec = IvParameterSpec(iv)
            cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivSpec)
        }
        return cipher.doFinal(data)
    }

    /**
     * AES Decryption
     */
    @JvmStatic
    fun aesDecrypt(
        key: ByteArray,
        iv: ByteArray,
        data: ByteArray,
        mode: AesMode = AesMode.CBC,
        padding: AesPadding = AesPadding.PKCS7
    ): ByteArray {
        val cipherMode = mode.name
        val paddingScheme = if (padding == AesPadding.PKCS7) "PKCS5Padding" else "NoPadding"
        val cipher = Cipher.getInstance("AES/$cipherMode/$paddingScheme")
        val secretKey = SecretKeySpec(key, "AES")

        if (mode == AesMode.ECB) {
            cipher.init(Cipher.DECRYPT_MODE, secretKey)
        } else {
            val ivSpec = IvParameterSpec(iv)
            cipher.init(Cipher.DECRYPT_MODE, secretKey, ivSpec)
        }
        return cipher.doFinal(data)
    }

    /**
     * Secure Random Bytes Generation
     */
    @JvmStatic
    fun randomBytes(length: Int): ByteArray {
        val random = SecureRandom()
        val bytes = ByteArray(length)
        random.nextBytes(bytes)
        return bytes
    }

    private fun hash(algo: String, input: String): String {
        val digest = MessageDigest.getInstance(algo)
        val hashBytes = digest.digest(input.toByteArray(Charsets.UTF_8))
        return hashBytes.joinToString("") { "%02x".format(it) }
    }

    private fun hmac(algo: String, key: String, data: String): String {
        val mac = Mac.getInstance(algo)
        mac.init(SecretKeySpec(key.toByteArray(Charsets.UTF_8), algo))
        return mac.doFinal(data.toByteArray(Charsets.UTF_8)).joinToString("") { "%02x".format(it) }
    }
}
