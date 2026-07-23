package com.luasoup.lexsoup

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Test

class LexSoupTest {

    @Test
    fun testParseHtmlAndCssQuery() {
        val html = """
            <html>
                <head><title>LexSoup Test</title></head>
                <body>
                    <div id="main" class="container">
                        <h1 class="header">Hello LexSoup</h1>
                        <p class="description">Fast Lexbor HTML Scraper</p>
                    </div>
                </body>
            </html>
        """.trimIndent()

        val doc = LexSoup.parse(html)
        assertNotNull(doc)

        val title = doc.title()
        assertNotNull(title)

        val header = doc.selectFirst(".header")
        assertNotNull(header)
        assertEquals("h1", header?.tagName())

        val elements = doc.select("p")
        assertNotNull(elements)
    }
}
