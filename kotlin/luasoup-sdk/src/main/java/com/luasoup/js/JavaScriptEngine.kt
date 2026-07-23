package com.luasoup.js

/**
 * QuickJS JavaScript Engine according to specs/091_javascript_module.md
 */
class JavaScriptEngine private constructor(private var handle: Long) {

    fun eval(script: String): String {
        if (handle == 0L) throw IllegalStateException("JavaScriptEngine closed")
        return nativeEval(handle, script)
    }

    fun close() {
        if (handle != 0L) {
            nativeClose(handle)
            handle = 0L
        }
    }

    companion object {
        @JvmStatic
        fun create(): JavaScriptEngine {
            val handle = nativeCreate()
            return JavaScriptEngine(handle)
        }

        @JvmStatic private external fun nativeCreate(): Long
        @JvmStatic private external fun nativeEval(handle: Long, script: String): String
        @JvmStatic private external fun nativeClose(handle: Long)
    }
}
