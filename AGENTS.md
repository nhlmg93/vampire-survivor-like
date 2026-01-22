# Agent Notes (vampire-survivor-like)

This repo is a tiny C11 + raylib playground. Today it builds a single
executable from `*.c` in the repo root.

Cursor/Copilot rules:

- No Cursor rules found (`.cursor/rules/` or `.cursorrules`).
- No Copilot instructions found (`.github/copilot-instructions.md`).

If any of those files are added later, follow them as higher priority.

## Fast Commands

- Build (debug): `make`
- Run (build + run): `make run`
- Release build: `make release`
- Clean: `make clean`
- Help (targets + overrides): `make help`

Build output defaults to `build/game`.

## Useful Overrides

- Use clang: `make CC=clang`
- Rename binary: `make TARGET=mygame`
- Point at a custom raylib install:
  - `make RAYLIB_INCLUDE_DIR=/path/include RAYLIB_LIB_DIR=/path/lib`
- Override link flags completely:
  - `make RAYLIB_LIBS="..."`

## Debugging/Inspection

- Show exact compile/link commands (dry-run): `make -n`
- Rebuild a single translation unit:
  - `make build/main.o`
  - `make build/foo.o`

## Lint / Static Analysis

There is no dedicated `make lint`. Treat “warnings clean” as lint: the default
build already uses `-Wall -Wextra -Wpedantic`.

Helpful local variants (no repo changes required):

- More warnings (clang example):
  - `make CC=clang WARNFLAGS="-Wall -Wextra -Wpedantic -Wconversion -Wshadow"`
- Sanitizers (debug-only experimentation):
  - `make CFLAGS_DBG="-O0 -g -DDEBUG -fsanitize=address,undefined"`
- Optional tools if installed (ad-hoc):
  - `cppcheck --enable=all --std=c11 .`
  - `clang-tidy *.c -- -std=c11`

Formatting:

- No `.clang-format` exists. If you run `clang-format`, keep changes scoped to
  the file you touched and avoid drive-by reformatting.

## Tests (Current + Preferred Pattern)

There is currently no automated unit/integration test harness.

- “Test” today means: `make` succeeds and `make run` behaves as expected.

Preferred future approach (so a single test is easy to run):

- Add `tests/` containing small standalone C programs (e.g. `tests/foo.c`).
- Add a `make test` target that builds/executes one test via a selector:
  - `make test TEST=foo` (runs only `tests/foo.c`)
- Convention: tests are named after the file stem; exit code indicates pass/fail.

If you implement tests, keep them dependency-light (plain C + `assert()` is OK).

## Codebase Shape

- `main.c`: prototype game loop
- `Makefile`: Linux-first raylib build
- `build/`: build artifacts (ignored via `.gitignore`)

The Makefile discovers sources using `$(wildcard $(SRC_DIR)/*.c)`. Placing a
new `.c` file in the repo root is enough to compile it into the binary.

## C / raylib Style Guidelines

These guidelines aim to keep changes consistent with the existing code and keep
iteration speed high.

### Headers / Imports

- Keep raylib included with quotes: `#include "raylib.h"`.
- Prefer this include order (matches current repo files):
  - Third-party (`"raylib.h"`)
  - Standard library (`<stdio.h>`, `<stdlib.h>`, ...)
  - Project headers (`"foo.h"`)
- Do not include headers you don’t use.

### Formatting

- Indentation: 2 spaces; avoid tabs.
- Keep line length reasonable (~100) when practical.
- Match the style of the file you are editing; don’t reformat unrelated code.
- Always put a space after keywords: `if (cond)` / `while (cond)`.
- Prefer braces for multi-line branches and non-trivial control flow.

### Naming

- Types (struct/enum/typedef): `UpperCamelCase`.
- Functions + variables: `lowerCamelCase`.
- Macros + enum values: `UPPER_SNAKE_CASE`.
- Booleans: prefix with `is`/`has`/`can`.

### Types / Constants / Math

- Use fixed-width integers when width matters (`int32_t`, `uint64_t`, ...).
- Use `size_t` for sizes/indices.
- Use `const` aggressively for values that should not change.
- Use float suffixes consistently (`1.0f`, `0.5f`).
- Prefer named constants over magic numbers (especially gameplay tuning).

### State / File Structure

- Prefer explicit structs (e.g. `GameState`, `Player`) over many globals.
- Use `static` for file-local functions/data.
- When the root file grows, split into `*.c`/`*.h` modules; keep headers minimal.

Suggested module boundaries (when needed):

- `game_state.*` (top-level loop + state)
- `player.*` (movement, draw)
- `enemy.*` (spawning, update)
- `util.*` (math, RNG helpers)

### Error Handling / Logging

- Check return values for allocations and file I/O (`malloc`, `fopen`, ...).
- For raylib loads, validate results where possible and fail fast.
- Prefer `TraceLog(LOG_ERROR, ...)` / `TraceLog(LOG_WARNING, ...)` over `printf`.
- In debug builds, `assert()` is fine for programmer errors.
- For multi-step init, use a single cleanup path:
  - `goto cleanup;` then `Unload*`/`free()` in reverse init order.

### Resource Lifetime

- Pair every `Load*` with the matching `Unload*`.
- Don’t load/unload heavy resources every frame.
- Keep phases distinct: init -> update -> draw -> shutdown.

### Gameplay Loop Conventions

- Avoid heap allocations inside the main loop unless necessary.
- Use `GetFrameTime()` for time-based movement once you move past a prototype.
- Keep update deterministic where possible; rendering should not mutate state.
