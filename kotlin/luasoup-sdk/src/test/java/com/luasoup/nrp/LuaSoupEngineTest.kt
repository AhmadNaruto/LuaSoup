package com.luasoup.nrp

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Test

class LuaSoupEngineTest {

    @Test
    fun testBridgeMetadata() {
        assertEquals("arm64-v8a", GeneratedNRPBridge.TARGET_ABI)
        assertEquals(172, GeneratedNRPBridge.TOTAL_MODULES)
    }

    @Test
    fun testEngineInitialization() {
        val engine = LuaSoupEngine.initialize()
        assertNotNull(engine)
        assertNotNull(engine.targetAbi)
    }

    @Test
    fun testEvalLuauScript() {
        val engine = LuaSoupEngine.initialize()
        val script = "return 'Hello from Luau'"
        val result = engine.evalLuau(script)
        assertNotNull(result)
    }

    @Test
    fun testParseHtml() {
        val engine = LuaSoupEngine.initialize()
        val html = "<div id='app'>Hello LuaSoup</div>"
        val result = engine.parseHtml(html)
        assertNotNull(result)
    }
}
