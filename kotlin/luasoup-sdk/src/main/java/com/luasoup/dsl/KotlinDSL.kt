package com.luasoup.dsl

import com.luasoup.lexsoup.Document
import com.luasoup.lexsoup.Element
import com.luasoup.lexsoup.Elements
import com.luasoup.lexsoup.LexSoup

/**
 * Idiomatic Kotlin DSL according to specs/109_kotlin_dsl.md
 */
class HtmlDslBuilder(private val htmlContent: String) {
    private var currentDocument: Document? = null
    private var currentSelection: Elements? = null
    private var firstElement: Element? = null

    fun select(cssQuery: String): HtmlDslBuilder {
        if (currentDocument == null) {
            currentDocument = LexSoup.parse(htmlContent)
        }
        currentSelection = currentDocument?.select(cssQuery)
        return this
    }

    fun first(): HtmlDslBuilder {
        firstElement = currentSelection?.first()
        return this
    }

    fun text(): String {
        return firstElement?.text() ?: currentSelection?.text() ?: ""
    }

    fun html(): String {
        return firstElement?.html() ?: currentSelection?.html() ?: ""
    }
}

fun htmlDsl(htmlContent: String, block: HtmlDslBuilder.() -> String): String {
    val builder = HtmlDslBuilder(htmlContent)
    return builder.block()
}
