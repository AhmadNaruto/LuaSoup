package com.luasoup.lexsoup

/**
 * Represents an HTML Document in LexSoup.
 */
class Document(handle: Long) : Element(handle) {

    /**
     * Get document title.
     */
    fun title(): String {
        return selectFirst("title")?.text() ?: ""
    }

    /**
     * Get <body> element.
     */
    fun body(): Element? {
        return selectFirst("body")
    }

    /**
     * Get <head> element.
     */
    fun head(): Element? {
        return selectFirst("head")
    }
}
