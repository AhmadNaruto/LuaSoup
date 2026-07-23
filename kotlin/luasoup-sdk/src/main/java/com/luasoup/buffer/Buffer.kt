package com.luasoup.buffer

/**
 * Buffer according to specs/094_buffer_module.md (immutable binary buffers, slicing, indexing)
 */
class Buffer(private val bytes: ByteArray) {

    val size: Int get() = bytes.size

    operator fun get(index: Int): Byte = bytes[index]

    fun slice(start: Int, end: Int): Buffer {
        return Buffer(bytes.copyOfRange(start, end))
    }

    fun toByteArray(): ByteArray = bytes.copyOf()

    companion object {
        @JvmStatic
        fun fromByteArray(bytes: ByteArray): Buffer = Buffer(bytes.copyOf())

        @JvmStatic
        fun fromString(str: String, charsetName: String = "UTF-8"): Buffer {
            return Buffer(str.toByteArray(charset(charsetName)))
        }
    }
}
