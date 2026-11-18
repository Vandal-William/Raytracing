# 2. Colour is its own class, not a Vector

## Context

A colour is three numbers, like a `Vector`. We need to decide whether `Colour` reuses `Vector`, or is a class of its own.

## Decision

`Colour` is a separate class. It holds three private doubles `_r`, `_g` and `_b`, readable through `r()`, `g()` and `b()`, with no other operation for now.

## Status

Accepted

## Consequences

- Colours and directions can't be mixed by accident: the compiler stops anyone from adding a colour to a position, or normalising a colour.
- `Colour` can grow its own rules later (mixing, clamping between 0 and 1, converting to 0–255 for an image file) without affecting `Vector`.
- `Vector`'s operations (`dot`, `length`, `normalised`, scaling) have no meaning for a colour, so `Colour` doesn't inherit a set of methods it would never use.
- There is some duplication between the two classes today (both hold three doubles with the same constructor shape). That's acceptable: DRY is about knowledge, not similar-looking lines, and the two classes represent different knowledge.

## Left out for now

- **Reusing `Vector` for `Colour`.** Would save the small duplication above, at the cost of letting a colour be added to a position, or normalised, which has no meaning. Worth reconsidering only if the duplication grows into real shared behaviour.
- **Clamping or validating `r`, `g`, `b` between 0 and 1.** Not decided yet: lights will eventually produce colours above 1, and we haven't decided whether to clamp or refuse them.
