package com.luasoup.json

/**
 * JsonArray according to specs/088_json_module.md
 */
class JsonArray(private val list: MutableList<Any?> = mutableListOf()) : MutableList<Any?> by list {
    fun getString(index: Int): String? = list.getOrNull(index) as? String
    fun getNumber(index: Int): Double? = (list.getOrNull(index) as? Number)?.toDouble()
    fun getBoolean(index: Int): Boolean? = list.getOrNull(index) as? Boolean
    fun getObject(index: Int): JsonObject? = list.getOrNull(index) as? JsonObject
    fun getArray(index: Int): JsonArray? = list.getOrNull(index) as? JsonArray
}
