# Generic raylib Makefile (Linux-first) for a small C project
# Usage:
#   make            # debug build
#   make run        # build + run
#   make release    # optimized build
#   make clean      # remove build artifacts
#
# You can override variables, e.g.:
#   make CC=clang
#   make RAYLIB_LIBS="-lraylib -lm -ldl -lpthread -lGL -lX11"

# ---- Project ----
TARGET      ?= game
SRC_DIR     ?= .
BUILD_DIR   ?= build

# If you add more .c files later, they'll be picked up automatically.
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS        := $(OBJS:.o=.d)

# ---- Toolchain ----
CC          ?= cc

# ---- raylib ----
# Assumes raylib is installed system-wide (e.g. apt/pacman/brew).
# If you built raylib yourself, you can set RAYLIB_INCLUDE_DIR/RAYLIB_LIB_DIR.
RAYLIB_INCLUDE_DIR ?=
RAYLIB_LIB_DIR     ?=

CPPFLAGS    += $(if $(RAYLIB_INCLUDE_DIR),-I$(RAYLIB_INCLUDE_DIR),)
LDFLAGS     += $(if $(RAYLIB_LIB_DIR),-L$(RAYLIB_LIB_DIR),)

# Default raylib link flags for Linux/X11.
# If you're on macOS/Windows, override RAYLIB_LIBS accordingly.
RAYLIB_LIBS ?= -lraylib -lm -ldl -lpthread -lGL -lX11

# ---- Flags ----
WARNFLAGS   ?= -Wall -Wextra -Wpedantic
CFLAGS_BASE ?= -std=c11 $(WARNFLAGS)
CFLAGS_DBG  ?= -O0 -g -DDEBUG
CFLAGS_REL  ?= -O2 -DNDEBUG

CFLAGS      += $(CFLAGS_BASE) $(CFLAGS_DBG)
LDLIBS      += $(RAYLIB_LIBS)

# ---- OS helpers ----
EXEEXT      ?=
RM          ?= rm -rf

.DEFAULT_GOAL := all

.PHONY: all release run clean help

all: $(BUILD_DIR)/$(TARGET)$(EXEEXT)

release: CFLAGS := $(CFLAGS_BASE) $(CFLAGS_REL)
release: $(BUILD_DIR)/$(TARGET)$(EXEEXT)

run: all
	./$(BUILD_DIR)/$(TARGET)$(EXEEXT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(TARGET)$(EXEEXT): $(OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Compile + generate dependency files (.d)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

help:
	@printf '%s\n' \
	  'Targets:' \
	  '  make / make all    Build debug binary' \
	  '  make release        Build optimized binary' \
	  '  make run            Build and run' \
	  '  make clean          Remove build artifacts' \
	  '' \
	  'Common overrides:' \
	  '  CC=clang' \
	  '  TARGET=mygame' \
	  '  RAYLIB_INCLUDE_DIR=/path/to/raylib/include' \
	  '  RAYLIB_LIB_DIR=/path/to/raylib/lib' \
	  '  RAYLIB_LIBS="..."'

-include $(DEPS)
