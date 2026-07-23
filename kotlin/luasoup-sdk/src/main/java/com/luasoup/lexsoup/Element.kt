package com.luasoup.lexsoup

/**
 * Represents an HTML Element in LexSoup (backed by C++ Lexbor engine).
 */
open class Element(internal val handle: Long) {

    /**
     * Query elements using CSS selector.
     */
    fun select(cssQuery: String): Elements {
        val handles = LexSoup.nativeSelect(handle, cssQuery) ?: longArrayOf()
        return Elements(handles.map { Element(it) })
    }

    /**
     * Query the first element matching the CSS selector.
     */
    fun selectFirst(cssQuery: String): Element? {
        val childHandle = LexSoup.nativeSelectFirst(handle, cssQuery)
        return if (childHandle != 0L) Element(childHandle) else null
    }

    /**
     * Get the combined text of this element and all its children.
     */
    fun text(): String = LexSoup.nativeText(handle)

    /**
     * Get the inner HTML string of this element.
     */
    fun html(): String = LexSoup.nativeHtml(handle)

    /**
     * Get the outer HTML string including this element's tag.
     */
    fun outerHtml(): String = LexSoup.nativeOuterHtml(handle)

    /**
     * Get an attribute value by key.
     */
    fun attr(key: String): String = LexSoup.nativeAttr(handle, key)

    /**
     * Check if an attribute key exists.
     */
    fun hasAttr(key: String): Boolean = LexSoup.nativeHasAttr(handle, key)

    /**
     * Get the tag name of this element (e.g. "div", "a", "h1").
     */
    fun tagName(): String = LexSoup.nativeTagName(handle)

    /**
     * Get element ID attribute.
     */
    fun id(): String = attr("id")

    /**
     * Get class attribute.
     */
    fun className(): String = attr("class")

    /**
     * Check if element has class.
     */
    fun hasClass(cls: String): Boolean {
        val classes = className().split("\\s+".toRegex())
        return classes.contains(cls)
    }

    override fun toString(): String = outerHtml()
}
