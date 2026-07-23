package com.luasoup.regex

/**
 * Regex according to specs/089_regex_module.md (compile, match, search, replace, split, captures)
 */
class Pattern private constructor(val patternString: String) {

    companion object {
        @JvmStatic
        fun compile(regex: String): Pattern = Pattern(regex)
    }

    fun match(input: String): Match? {
        val re = Regex(patternString)
        val m = re.find(input) ?: return null
        return Match(m.value, m.groupValues)
    }

    fun search(input: String): Boolean {
        return Regex(patternString).containsMatchIn(input)
    }

    fun replace(input: String, replacement: String): String {
        return Regex(patternString).replace(input, replacement)
    }

    fun split(input: String): List<String> {
        return Regex(patternString).split(input)
    }
}

data class Match(val value: String, val captures: List<String>)
