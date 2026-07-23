package com.luasoup.utility

import java.util.UUID

/**
 * Utility Module according to specs/095_utility_module.md (UUID, Version, Stopwatch, Timer, Environment)
 */
object Utility {

    @JvmStatic
    fun uuid(): String = UUID.randomUUID().toString()

    @JvmStatic
    fun version(): String = "1.0.0"

    @JvmStatic
    fun nowMillis(): Long = System.currentTimeMillis()
}
