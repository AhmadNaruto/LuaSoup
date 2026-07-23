package com.luasoup.url

import java.net.URI
import java.net.URLDecoder
import java.net.URLEncoder

/**
 * URL Module according to specs/092_url_module.md
 */
class Url private constructor(private val uri: URI) {

    fun normalize(): String = uri.normalize().toString()

    fun getQueryParam(key: String): String? {
        val query = uri.query ?: return null
        return query.split("&")
            .map { it.split("=") }
            .firstOrNull { it.size == 2 && it[0] == key }
            ?.get(1)
    }

    fun setQueryParam(key: String, value: String): Url {
        val base = "${uri.scheme}://${uri.authority}${uri.path}"
        val existingQuery = uri.query
        val newQuery = if (existingQuery.isNull_or_empty()) {
            "$key=$value"
        } else {
            val params = existingQuery.split("&").toMutableList()
            params.removeAll { it.startsWith("$key=") }
            params.add("$key=$value")
            params.joinToString("&")
        }
        return parse("$base?$newQuery")
    }

    override fun toString(): String = uri.toString()

    companion object {
        @JvmStatic
        fun parse(urlString: String): Url = Url(URI.create(urlString))

        @JvmStatic
        fun percentEncode(input: String): String = URLEncoder.encode(input, "UTF-8")

        @JvmStatic
        fun percentDecode(input: String): String = URLDecoder.decode(input, "UTF-8")
    }
}

private fun String?.isNull_or_empty(): Boolean = this == null || this.isEmpty()
