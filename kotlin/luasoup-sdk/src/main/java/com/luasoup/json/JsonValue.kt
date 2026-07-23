package com.luasoup.json

/**
 * JsonValue according to specs/088_json_module.md
 */
sealed class JsonValue {
    data class StringVal(val value: String) : JsonValue()
    data class NumberVal(val value: Double) : JsonValue()
    data class BoolVal(val value: Boolean) : JsonValue()
    object NullVal : JsonValue()
    data class ObjectVal(val value: JsonObject) : JsonValue()
    data class ArrayVal(val value: JsonArray) : JsonValue()
}
