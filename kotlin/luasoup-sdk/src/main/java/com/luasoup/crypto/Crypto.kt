package com.luasoup.crypto

import java.security.MessageDigest
import javax.crypto.Mac
import javax.crypto.spec.SecretKeySpec

/**
 * Crypto Module according to specs/090_crypto_module.md (Mbed TLS / Native Crypto)
 */
object Crypto {

    @JvmStatic
    fun md5(data: String): String = hash("MD5", data)

    @JvmStatic
    fun sha1(data: String): String = hash("SHA-1", data)

    @JvmStatic
    fun sha256(data: String): String = hash("SHA-256", data)

    @JvmStatic
    fun sha512(data: String): String = hash("SHA-512", data)

    @JvmStatic
    fun hmacSha256(key: String, data: String): String {
        val mac = Mac.getInstance("HmacSHA256")
        mac.init(SecretKeySpec(key.toByteArray(Charsets.UTF_8), "HmacSHA256"))
        return mac.doFinal(data.toByteArray(Charsets.UTF_8)).joinToString("") { "%02x".format(it) }
    }

    private fun hash(algo: String, input: String): String {
        val digest = MessageDigest.getInstance(algo)
        val hashBytes = digest.digest(input.toByteArray(Charsets.UTF_8))
        return hashBytes.joinToString("") { "%02x".format(it) }
    }
}
