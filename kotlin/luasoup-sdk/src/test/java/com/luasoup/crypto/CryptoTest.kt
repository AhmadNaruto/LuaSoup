package com.luasoup.crypto

import org.junit.Assert.assertArrayEquals
import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Test

class CryptoTest {

    @Test
    fun testAesEncryptionDecryption() {
        val key = "1234567890123456".toByteArray(Charsets.UTF_8) // 16 bytes = AES-128
        val iv = "1234567890123456".toByteArray(Charsets.UTF_8)
        val plaintext = "Hello LuaSoup AES Encryption".toByteArray(Charsets.UTF_8)

        val encrypted = Crypto.aesEncrypt(key, iv, plaintext, AesMode.CBC, AesPadding.PKCS7)
        assertNotNull(encrypted)

        val decrypted = Crypto.aesDecrypt(key, iv, encrypted, AesMode.CBC, AesPadding.PKCS7)
        assertArrayEquals(plaintext, decrypted)
    }

    @Test
    fun testRandomBytes() {
        val random = Crypto.randomBytes(32)
        assertEquals(32, random.size)
    }

    @Test
    fun testHashes() {
        assertEquals(64, Crypto.sha256("LuaSoup").length)
        assertEquals(32, Crypto.md5("LuaSoup").length)
    }
}
