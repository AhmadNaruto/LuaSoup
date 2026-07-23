package com.luasoup.nrp

data class Handle(val id: Long) {
    val isValid: Boolean get() = id != 0L
    val index: Int get() = (id and 0xFFFFFFFFL).toInt()
    val generation: Int get() = ((id shr 32) and 0xFFFFL).toInt()
    val typeId: Int get() = ((id shr 48) and 0xFFL).toInt()

    companion object {
        val NULL = Handle(0L)
    }
}
