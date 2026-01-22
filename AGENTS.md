# Agent Notes (vampire-survivor-like)

This repo is a tiny C11 + raylib playground. It currently builds a single
executable from `*.c` in the repo root.

No Cursor rules were found (`.cursor/rules/` or `.cursorrules`).
No Copilot instructions were found (`.github/copilot-instructions.md`).

## Fast Commands

- Build (debug): `make`
- Run: `make run`
- Release build: `make release`
- Clean build artifacts: `make clean`
- Help (targets + overrides): `make help`

Build output defaults to `build/game`.

### Common Overrides

- Use clang: `make CC=clang`
- Change binary name: `make TARGET=mygame`
- Point at custom raylib install:
  - `make RAYLIB_INCLUDE_DIR=/path/include RAYLIB_LIB_DIR=/path/lib`
- Override link flags completely:
  - `make RAYLIB_LIBS="..."`

### Rebuild One File

Make’s pattern rule allows compiling a single translation unit:

- Compile only `main.c`: `make build/main.o`
- Compile only `foo.c`: `make build/foo.o`

(The final link step happens when you build the binary: `make` / `make all`.)

### See The Exact Compile/Link Commands

- Dry-run: `make -n`

## Lint / Static Analysis

There is no dedicated lint target yet; the default build already enables
warnings (`-Wall -Wextra -Wpedantic`) and should be treated as the baseline
“lint” signal.

Practical options that work without repo changes:

- Turn warnings up (clang example):
  - `make CC=clang WARNFLAGS="-Wall -Wextra -Wpedantic -Wconversion -Wshadow"`
- Quick local sanitizers (debug-only experimentation):
  - `make CFLAGS_DBG="-O0 -g -DDEBUG -fsanitize=address,undefined"`

Formatting:

- No `.clang-format` is present. If you run `clang-format`, keep output
  consistent within the file you touched, and avoid drive-by reformatting.

## Tests

There is currently no automated unit/integration test harness in this repo.

- “Test” right now means: `make` succeeds and `make run` behaves as expected.
- There is no concept of “run a single test” yet.

If you add tests later, prefer a simple, tool-light approach:

- Add `tests/` with small C test programs (or a tiny framework like Unity).
- Add `make test` and a single-test selector (example convention):
  - `make test TEST=foo` (not implemented today).

## Codebase Shape

- `main.c`: prototype game loop
- `Makefile`: generic Linux-first raylib build
- `build/`: build artifacts (ignored via `.gitignore`)

The Makefile discovers sources using `$(wildcard $(SRC_DIR)/*.c)`.
If you add files, placing them in the same directory is enough to compile.

## C / raylib Style Guidelines

These guidelines aim to keep changes consistent with the existing code and
keep iteration speed high.

### Headers and Imports

- Keep raylib include as-is: `#include "raylib.h"`.
- When adding headers, use a consistent order within each file:
  - Standard library headers (`<stdio.h>`, `<stdlib.h>`, ...)
  - Third-party (`"raylib.h"`)
  - Project headers (`"foo.h"`)
- Do not include headers you don’t use.

### Formatting

- Indentation: 2 spaces; avoid tabs.
- Keep line length reasonable (~100) when practical.
- Prefer a single style per file; when editing existing code, match the local
  style instead of reformatting unrelated blocks.
- Always put a space after keywords: `if (cond)` / `while (cond)`.

Braces:

- Prefer braces for non-trivial control flow.
- If you change control flow in a block, consider adding braces to reduce
  “dangling else” / accidental single-line bugs.

### Naming

- Types: `UpperCamelCase` (e.g. `GameScreen`, `Player`, `Enemy`).
- Enum values and macros: `UPPER_SNAKE_CASE`.
- Variables and functions: `lowerCamelCase` (matches existing `currentScreen`).
- Booleans: prefix with `is`, `has`, `can` (e.g. `isDead`, `hasHit`).

### Types, Constants, and Math

- Use C99/C11 fixed-width integers when the width matters (`int32_t`, etc.).
- Use `size_t` for sizes/indices when appropriate.
- Use `const` aggressively for values that should not change.
- Use float suffixes consistently (`1.0f` not `1.0`).
- Prefer named constants over magic numbers, especially in gameplay tuning.

### State and File Structure

- Prefer keeping state in explicit structs (e.g. `GameState`, `Player`) instead
  of many globals.
- Use `static` for file-local functions and data.
- When the file grows, split into `*.c`/`*.h` modules and keep headers minimal.

Suggested module boundaries (when needed):

- `game_state.*` (top-level loop + state)
- `player.*` (movement, draw)
- `enemy.*` (spawning, update)
- `util.*` (math, RNG helpers)

### Error Handling and Logging

- Check return values for allocations and file IO (`malloc`, `fopen`, etc.).
- Prefer `TraceLog(LOG_ERROR, ...)` / `TraceLog(LOG_WARNING, ...)` for runtime
  diagnostics instead of `printf`.
- In debug builds, `assert()` is fine for programmer errors.
- For multi-step init, use a single cleanup path (common C pattern):
  - `goto cleanup;` then unload/free everything that was successfully created.

### Resource Lifetime

- Pair every `Load*` with the matching `Unload*`.
- Do not load/unload heavy resources every frame.
- Keep “init / update / draw / shutdown” phases distinct.

### Gameplay Loop Conventions

- Avoid heap allocations inside the main loop unless necessary.
- Use `GetFrameTime()` for time-based movement when you move past a prototype
  with fixed per-frame deltas.
- Keep update deterministic where possible; rendering should not mutate state.
