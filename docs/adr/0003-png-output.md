# 3. Save images as PNG with LodePNG

## Context

The client opens our images in ordinary viewers, so we save them as PNG. PNG is compressed and has checksums, so we use a library rather than write it ourselves.

We compared four options:

- **libpng.** The reference library. Its API is in C and takes many calls to save one image, and it is not in our Docker image.
- **stb_image_write.** A single header, in the public domain. Its API is in C with raw pointers, and its PNG files are larger.
- **LodePNG.** One `.cpp` and one `.h`, under the zlib licence, with no dependencies. Its API is in C++ and uses `std::vector`. It is slower than the others at saving.
- **Writing PPM ourselves.** No library is needed, but most viewers can't open PPM, and the files are far bigger.

## Decision

We will save images with LodePNG. CMake downloads it with `FetchContent`, like Catch2, pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409`, because LodePNG has no releases.

Only `src/output/` uses LodePNG, behind our own interface `ImageSaver`. Changing library or format then means writing one new class.

## Status

Accepted

## Consequences

- The client can open our images in ordinary viewers.
- LodePNG is two files with no dependencies, and it is not added to our Docker image: CMake downloads it.
- The first configure needs internet access to download LodePNG from its repository, as it already does for Catch2.
- LodePNG has no releases, so we pin a commit. Upgrading it is a manual change to the pinned commit.
- LodePNG is slower than the other libraries at saving. We accept this for its simple C++ API.
- The rest of the code does not include LodePNG. Changing library or format means a new class behind `ImageSaver`, and no change to the code that calls it.
- `ImageSaver` is one more layer, and for now it has a single implementation.
