package com.luasoup.nrp

/**
 * Idiomatic Kotlin High-Level API for LuaSoup Native Runtime Platform (NRP).
 */
class LuaSoupEngine private constructor(val targetAbi: String) {

    companion object {
        private var isInitialized = false

        /**
         * Initialize the native LuaSoup engine runtime.
         */
        @JvmStatic
        fun initialize(): LuaSoupEngine {
            val abi = try {
                NRP.nativeGetTargetArch()
            } catch (e: UnsatisfiedLinkError) {
                GeneratedNRPBridge.TARGET_ABI
            }

            try {
                NRP.nativeInit()
            } catch (e: UnsatisfiedLinkError) {
                // Mock / desktop fallback
            }

            isInitialized = true
            return LuaSoupEngine(abi)
        }
    }

    /**
     * Evaluate Luau script in sandboxed VM.
     */
    fun evalLuau(script: String): String {
        return try {
            NRP.nativeEvalLuau(script)
        } catch (e: UnsatisfiedLinkError) {
            "SDK Fallback: $script"
        }
    }

    /**
     * Parse HTML string using high-performance C++ HTML/DOM module.
     */
    fun parseHtml(html: String): String {
        return try {
            NRP.nativeParseHTML(html)
        } catch (e: UnsatisfiedLinkError) {
            "<html><body>$html</body></html>"
        }
    }
}
