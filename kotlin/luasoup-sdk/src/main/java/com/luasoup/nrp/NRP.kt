package com.luasoup.nrp

/**
 * Low-level JNI binding interface for LuaSoup Native Runtime Platform (NRP).
 */
object NRP {
    init {
        try {
            System.loadLibrary("nrp_core")
        } catch (e: UnsatisfiedLinkError) {
            // In unit tests or mock environments where native library is pre-loaded or mocked
        }
    }

    @JvmStatic
    external fun nativeGetTargetArch(): String

    @JvmStatic
    external fun nativeInit(): Boolean

    @JvmStatic
    external fun nativeEvalLuau(script: String): String

    @JvmStatic
    external fun nativeParseHTML(html: String): String
}
