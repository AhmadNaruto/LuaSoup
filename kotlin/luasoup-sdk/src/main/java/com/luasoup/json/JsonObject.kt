package com.luasoup.json

/**
 * JsonObject according to specs/088_json_module.md
 */
class JsonObject(private val map: MutableMap<String, Any?> = mutableMapOf()) : MutableMap<String, Any?> by map {
    fun getString(key: String): String? = map[key] as? String
    fun getNumber(key: String): Double? = (map[key] as? Number)?.toDouble()
    fun getBoolean(key: String): Boolean? = map[key] as? Boolean
    fun getObject(key: String): JsonObject? = map[key] as? JsonObject
    fun getArray(key: String): JsonArray? = map[key] as? JsonArray
}
