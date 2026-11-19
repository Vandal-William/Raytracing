# 4. Coordinate system: x right, y up, z forward, pixels from the top left

## Context

We need a fixed convention for the 3D world and for the image grid, so that every class agrees on what a number means.

## Decision

In the world: x goes to the right, y goes up, and z goes forward, away from the eye. The camera looks along +z. This is a left-handed system.

In the image: pixels are counted from the top left, as in a text file or a PNG. Column 0 is on the left, row 0 is at the top. Columns go right, rows go down.

Converting from a pixel to a world point turns `y` round: `y = height / 2 - row - 0.5`, because rows go down and y goes up.

## Status

Accepted

## Consequences

- Every class that builds a `Ray` from a pixel (`Camera::rayThroughPixel`) must apply this turn, and its tests check it with an off-centre pixel, where a missing turn is caught.
- Matches how image files and image libraries (including LodePNG) count pixels, so `Image` and `PngSaver` need no conversion of their own.
- A single ray, as in the pinhole spike, doesn't care about handedness. It will matter once rays are transformed (e.g. a camera that doesn't look straight along z).

## Left out for now

- **Right-handed coordinates** (looking along −z, as in *Ray Tracing in One Weekend*). Either convention works; we keep ours for consistency with the spike's first ray, written before this ADR.
