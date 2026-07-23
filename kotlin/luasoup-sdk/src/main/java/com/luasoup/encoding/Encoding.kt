package com.luasoup.encoding

import java.net.URLDecoder
import java.net.URLEncoder
import java.util.Base64

/**
 * Encoding Module according to specs/093_encoding_module.md (UTF-8, UTF-16, Base64, Hex, URL Encoding)
 */
object Encoding {

    @JvmStatic
    fun toBase64(data: ByteArray): String = Base64.getEncoder().encodeToString(data)

    @JvmStatic
    fun fromBase64(base64Str: String): ByteArray = Base64.getDecoder().decode(base64Str)

    @JvmStatic
    fun toHex(data: ByteArray): String = data.joinToString("") { "%02x".format(it) }

    @JvmStatic
    fun fromHex(hexStr: String): ByteArray {
        val len = hexStr.length
        val data = ByteArray(len / 2)
        for (i in 0 until len step 2) {
            data[i / 2] = ((Character.digit(hexStr[i], 16) shl 4) + Character.digit(hexStr[i + 1], 16)).toByte()
        }
        return data
    }

    @JvmStatic
    fun encodeUrl(input: String): String = URLEncoder.encode(input, "UTF-8")

    @JvmStatic
    fun decodeUrl(input: String): String = URLDecoder.decode(input, "UTF-8")
}
