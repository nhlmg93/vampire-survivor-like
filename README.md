# vampire-survivor-like

A tiny C + [raylib](https://www.raylib.com/) playground for
experimenting with a Vampire Survivors-style game loop.

## Requirements

- A C11 compiler (`cc`, `gcc`, or `clang`)
- `make`
- `raylib` installed system-wide

On Linux you can usually install raylib
via your package manager (or build it from source).

## Build

```sh
make
```

Build output: `build/game`

## Run

```sh
make run
```

## Release build

```sh
make release
```

## Controls

- Arrow keys: move the player rectangle
- ESC / window close: quit

## Project layout

- `main.c`: game prototype
- `Makefile`: build + run targets
- `build/`: build artifacts

## Notes / Customizing raylib paths

If raylib is not installed in a standard location,
you can point the Makefile at it:

```sh
make RAYLIB_INCLUDE_DIR=/path/to/raylib/include \
     RAYLIB_LIB_DIR=/path/to/raylib/lib
```

You can also override the link flags directly:

```sh
make RAYLIB_LIBS="..."
```
