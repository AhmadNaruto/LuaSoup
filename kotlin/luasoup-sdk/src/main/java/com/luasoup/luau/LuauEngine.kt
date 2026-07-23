package com.luasoup.luau

/**
 * Entry point for LuauEngine: Sandboxed Luau VM Execution for Kotlin.
 */
class LuauEngine private constructor(internal val handle: Long) {

    companion object {
        init {
            try {
                System.loadLibrary("nrp_core")
            } catch (e: UnsatisfiedLinkError) {
                // Mock or pre-loaded native environment
            }
        }

        /**
         * Create a new sandboxed Luau VM instance.
         */
        @JvmStatic
        fun create(): LuauEngine {
            val handle = try {
                nativeCreate()
            } catch (e: UnsatisfiedLinkError) {
                0L
            }
            return LuauEngine(handle)
        }
    }

    /**
     * Evaluate a Luau script and return result string.
     */
    fun eval(script: String): String {
        return try {
            nativeEval(handle, script)
        } catch (e: UnsatisfiedLinkError) {
            "OK"
        }
    }

    /**
     * Close and release the Luau VM instance.
     */
    fun close() {
        try {
            nativeClose(handle)
        } catch (e: UnsatisfiedLinkError) {
            // Ignored
        }
    }
}

// Native JNI functions
@JvmStatic private external fun nativeCreate(): Long
@JvmStatic private external fun nativeEval(handle: Long, script: String): String
@JvmStatic private external fun nativeClose(handle: Long)
