# HTML Module

## Overview

The HTML Module SHALL provide high-performance HTML parsing using Lexbor.

Lexbor SHALL remain completely hidden behind the public API.

Replacing Lexbor SHALL NOT affect public APIs.

---

## Responsibilities

The HTML Module SHALL provide:

- HTML parsing
- CSS selector engine
- DOM traversal
- DOM querying
- DOM serialization
- DOM inspection

---

## Public Objects

The HTML Module SHALL expose:

- Document
- Element
- Elements
- Node
- Attribute

Only these objects SHALL be public.

---

## Selector Engine

The selector engine SHALL support:

- CSS Level 4 selectors whenever supported
- selector chains
- descendant selectors
- child selectors
- sibling selectors
- attribute selectors
- pseudo selectors supported by Lexbor

---

## Selector Chain

The Runtime SHALL support chained selectors.

Examples include:

```
"#main"

"#main .item"

"#main > ul"

"#main > ul > li"

"#main .chapter p"

"div.content > ul.items > li.active"

"#div.li > .chbox1 p"
```

Compiled selector execution SHOULD be optimized.

---

## Compiled Selectors

Selectors SHALL be compiled automatically.

Repeated selector execution SHOULD reuse compiled selector plans.

Compilation SHALL remain transparent to applications.

---

## JSoup Compatibility

The HTML Module SHALL adopt JSoup-style APIs whenever practical.

Supported APIs SHALL include:

- parse()
- select()
- selectFirst()
- selectLast()
- selectXpath() (future)
- matches()
- closest()
- parent()
- children()
- child()
- nextElementSibling()
- previousElementSibling()

Behavior SHALL remain predictable.

---

## Attribute Access

HTML attributes SHALL behave as Kotlin properties whenever practical.

Example:

```
element.id

element.className

element.href

element.src

element.title
```

Dynamic attributes SHALL also be supported.

Example:

```
element.attr("data-id")

element.attr("style")
```

---

## Property Access

Frequently used HTML properties SHALL become direct properties.

Examples:

```
element.text

element.html

element.outerHtml

element.tagName

element.parent

element.children

document.title

document.body

document.head
```

Method wrappers SHOULD be avoided when properties are sufficient.

---

## Lazy DOM

DOM traversal SHALL remain lazy whenever practical.

Children SHALL NOT be materialized until accessed.

---

## Elements Collection

Elements SHALL support:

- indexing
- iteration
- filtering
- mapping
- searching
- chaining

Behavior SHALL remain identical across Kotlin and Luau.

---

