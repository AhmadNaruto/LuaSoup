package com.luasoup.lexsoup

/**
 * Collection of LexSoup Element items with JSoup-like utility operations.
 */
class Elements(private val elementList: List<Element>) : List<Element> by elementList {

    /**
     * Get combined text of all elements in this collection.
     */
    fun text(): String = elementList.joinToString(" ") { it.text() }

    /**
     * Get combined outer HTML of all elements.
     */
    fun html(): String = elementList.joinToString("\n") { it.html() }

    /**
     * Get attribute value from the first matching element.
     */
    fun attr(key: String): String = elementList.firstOrNull()?.attr(key) ?: ""

    /**
     * Filter elements using a CSS selector query across all items.
     */
    fun select(cssQuery: String): Elements {
        val result = mutableListOf<Element>()
        for (elem in elementList) {
            result.addAll(elem.select(cssQuery))
        }
        return Elements(result)
    }

    /**
     * Get the first element in the collection, or null.
     */
    fun first(): Element? = elementList.firstOrNull()

    /**
     * Get the last element in the collection, or null.
     */
    fun last(): Element? = elementList.lastOrNull()
}
