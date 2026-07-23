package com.luasoup.lexsoup

/**
 * Entry point for LexSoup: High-Performance C++ Lexbor HTML DOM Scraper & Parser for Kotlin.
 */
object LexSoup {

    init {
        try {
            System.loadLibrary("nrp_core")
        } catch (e: UnsatisfiedLinkError) {
            // Mock or pre-loaded native environment
        }
    }

    /**
     * Parse an HTML string into a Document.
     */
    @JvmStatic
    fun parse(html: String): Document {
        val handle = try {
            nativeParse(html)
        } catch (e: UnsatisfiedLinkError) {
            0L
        }
        return Document(handle)
    }

    /**
     * Parse an HTML body fragment into a Document.
     */
    @JvmStatic
    fun parseBodyFragment(bodyHtml: String): Document {
        return parse("<html><body>$bodyHtml</body></html>")
    }

    // --- Native JNI Functions ---
    @JvmStatic external fun nativeParse(html: String): Long
    @JvmStatic external fun nativeSelect(handle: Long, cssQuery: String): LongArray?
    @JvmStatic external fun nativeSelectFirst(handle: Long, cssQuery: String): Long
    @JvmStatic external fun nativeText(handle: Long): String
    @JvmStatic external fun nativeHtml(handle: Long): String
    @JvmStatic external fun nativeOuterHtml(handle: Long): String
    @JvmStatic external fun nativeAttr(handle: Long, key: String): String
    @JvmStatic external fun nativeHasAttr(handle: Long, key: String): Boolean
    @JvmStatic external fun nativeTagName(handle: Long): String
    @JvmStatic external fun nativeFreeHandle(handle: Long)
}
