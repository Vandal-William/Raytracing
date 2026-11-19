# 5. A shape has a material, rather than being one

## Context

Every shape (a sphere, a plane, more later) needs to know how it reacts to light: what colour it is, and how it shades itself under Lambert's law. We need to decide whether that behaviour lives in the shape itself, or in a separate object.

We compared two approaches:

- **Inheritance.** `Sphere` grows subclasses per material: `MatteSphere`, `MirrorSphere`. `Plane` would need the same: `MattePlane`, `MirrorPlane`. Every new shape or new material multiplies the number of classes (shapes × materials).
- **Composition.** `Sphere` and `Plane` each hold one `Material`, and hand it the shading work. A new shape or a new material is one new class (shapes + materials).

## Decision

A shape has a `Material`, kept in a private field, rather than being one. `Sphere`'s and `Plane`'s constructors take a `Material`, and shading (`Material::shade`) is delegated to it. This follows "favour object composition over class inheritance" (*Design Patterns*, 1994).

## Status

Accepted

## Consequences

- Adding a new material (e.g. a mirror) needs one new class, not one new subclass per existing shape.
- A shape's material can change at runtime, which isn't possible with its class.
- `Sphere` and `Plane` don't know how shading works; they only hand the hit's normal and the light direction to their `Material`. That's delegation, and keeps Lambert's law in one place.
- The shape and its material are still two objects passed around together at a hit (via `Hit::material`), which is a small amount of extra structure compared to a single class.

## Left out for now

- **A material hierarchy of its own** (e.g. `Material` as an interface with `MatteMaterial`, `MirrorMaterial`). Worth it once we have more than one kind of material; for now there is only Lambert's law.
