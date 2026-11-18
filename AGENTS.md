# AGENTS.md

## How we work

- Test-driven development: write a failing test first, then only enough code to make it pass.
- Expected values in tests come from the maths, not from running the code. If a test fails, ask before changing what it expects.
- One small step at a time. Do only what is asked for, nothing more.
- Keep the C++ simple. No advanced features unless asked.
- Don't build or run anything directly on the host. The commands below run inside the Docker container (see [README.md](README.md)).

## Build and test commands

Run from the host (enters the container automatically):

- `npm run build:release` / `npm run build:debug` — build only
- `npm start` / `npm run debug` — build then run the binary
- `npm test` / `npm run test:debug` — build then run the tests

Inside the container (e.g. after `docker run --rm -it raytracing bash`):

- `make test` — build Release and run the tests
- `make build-release` / `make build-debug` / `make start` / `make debug` / `make test-debug`

## Source layout

New classes go in the folder of their concept, under `src/`, and their tests in the matching folder under `tests/`. Includes start from `src/`, for example `#include "math/vector.h"`.
