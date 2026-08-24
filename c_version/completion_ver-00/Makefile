# ============================================================
# Universal C Makefile
# Usage:
#   make            — build all (release)
#   make run        — build and run
#   make debug      — build with debug symbols
#   make file=foo.c — quick compile single file
#   make clean      — remove binaries
#   make help       — show this help
# ============================================================

# --- Compiler & Tools ---
CC       ?= gcc
RM       ?= rm -f
MKDIR    ?= mkdir -p

# --- Project Sources (auto-discover) ---
SRC_DIRS    ?= .
SOURCES     := $(shell find $(SRC_DIRS) -name '*.c' -not -path './build/*')
TARGET_DIR  ?= build

# --- Main target ---
# (Change this to your main binary name, or leave as the directory basename)
TARGET      ?= $(notdir $(shell pwd))

# --- Object files (for full build) ---
OBJECTS     := $(patsubst %.c,$(TARGET_DIR)/%.o,$(SOURCES))

# --- Mode flags ---
# release: optimize, no debug
CFLAGS_RELEASE := -O2 -DNDEBUG
# debug: no opt, symbols, sanitizers
CFLAGS_DEBUG   := -O0 -g3 -DDEBUG -fsanitize=address -fsanitize=undefined
LDFLAGS_DEBUG  := -fsanitize=address -fsanitize=undefined

# --- Warnings ---
CWARNS   := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 \
            -Wconversion -Wstrict-prototypes -Wmissing-prototypes

# --- Default: release ---
MODE     ?= release
CFLAGS   := $(CWARNS) $(CFLAGS_RELEASE)
LDFLAGS  :=
LIBS     :=

# Merge mode-specific flags
ifeq ($(MODE),debug)
  CFLAGS := $(CWARNS) $(CFLAGS_DEBUG)
  LDFLAGS := $(LDFLAGS_DEBUG)
endif

# --- Verbosity ---
V ?= 0
ifeq ($(V),0)
  Q := @
else
  Q :=
endif

# ============================================================
# Most commonly used libraries (uncomment as needed)
# ============================================================
# LIBS += -lm                    # Math (sin, cos, sqrt, ...)
# LIBS += -lpthread              # POSIX threads
# LIBS += -ldl                   # Dynamic loading (dlopen)
# LIBS += -lrt                   # Real-time (clock_gettime, shm)
# LIBS += -lutil                 # PTY operations (forkpty, openpty)
#
# --- glib-2.0 (GLib, GObject, GIO) ---
# LIBS += $(shell pkg-config --cflags --libs glib-2.0)
#
# --- dbus-1 (libdbus) ---
# LIBS += $(shell pkg-config --cflags --libs dbus-1)
#
# --- dbus-glib (GLib + D-Bus integration) ---
# LIBS += $(shell pkg-config --cflags --libs dbus-glib-1 dbus-1 glib-2.0)
#
# --- libudev (device discovery) ---
# LIBS += $(shell pkg-config --cflags --libs libudev)
#
# --- libcurl / libsoup (HTTP) ---
# LIBS += $(shell pkg-config --cflags --libs libcurl)
# LIBS += $(shell pkg-config --cflags --libs libsoup-2.4)
#
# --- ncurses (TUI) ---
# LIBS += -lncurses
#
# --- readline (line editing) ---
# LIBS += -lreadline
#
# --- libconfig / libini (config files) ---
# LIBS += -lconfig
#
# --- libpcap (packet capture) ---
# LIBS += $(shell pkg-config --cflags --libs libpcap)
#
# --- libxml-2.0 ---
# LIBS += $(shell pkg-config --cflags --libs libxml-2.0)
#
# --- jansson / yajl (JSON) ---
# LIBS += $(shell pkg-config --cflags --libs jansson)
#
# --- openssl (crypto, TLS) ---
# LIBS += $(shell pkg-config --cflags --libs openssl)
#
# --- capstone (disassembly) ---
# LIBS += $(shell pkg-config --cflags --libs capstone)

# ============================================================
# Targets
# ============================================================

.PHONY: all run debug clean help

all: $(TARGET_DIR)/$(TARGET)

# --- Full build: link all objects ---
$(TARGET_DIR)/$(TARGET): $(OBJECTS)
	@echo "  LD    $@"
	$(Q)$(MKDIR) $(@D)
	$(Q)$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)

# --- Compile each .c → .o ---
$(TARGET_DIR)/%.o: %.c
	@echo "  CC    $<"
	$(Q)$(MKDIR) $(@D)
	$(Q)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# --- Quick compile: single file ---
file: $(file)
ifeq ($(file),)
	@echo "Usage: make file=path/to/foo.c [LIBS='-lfoo']"
	@exit 1
endif
	@echo "  CC    $(file) → $(TARGET_DIR)/$(notdir $(file:.c=))"
	$(Q)$(MKDIR) $(TARGET_DIR)
	$(Q)$(CC) $(CFLAGS) -o $(TARGET_DIR)/$(notdir $(file:.c=)) $(file) $(LDFLAGS) $(LIBS)

# --- Run ---
run: all
	@echo "  RUN   $(TARGET_DIR)/$(TARGET)"
	$(Q)$(TARGET_DIR)/$(TARGET)

# --- Debug mode ---
debug: MODE := debug
debug: all

# --- Bear wrapper (for LSP compile_commands.json) ---
bear:
	@bear -- make $(filter-out bear,$(MAKECMDGOALS))

# --- Clean ---
clean:
	@echo "  RM    $(TARGET_DIR)"
	$(Q)$(RM) -r $(TARGET_DIR)

# --- Help ---
help:
	@echo "Targets:"
	@echo "  make [MODE=release]   — Build all (release, default)"
	@echo "  make debug            — Build with debug symbols + sanitizers"
	@echo "  make run              — Build + run"
	@echo "  make file=foo.c       — Quick-compile a single source"
	@echo "  make clean            — Remove build/ directory"
	@echo "  make bear             — Generate compile_commands.json"
	@echo ""
	@echo "Variables:"
	@echo "  MODE=release|debug   — Build mode"
	@echo "  V=1                  — Verbose output"
	@echo "  LIBS='-lfoo -lbar'   — Extra libraries"
	@echo "  SRC_DIRS='. ./lib'   — Source directories (default: .)"
	@echo "  CC=gcc|clang         — Compiler"
	@echo ""
	@echo "Example:"
	@echo "  make file=d-bus/tmp.c"
	@echo "  make file=upower.c LIBS=\"\$$(pkg-config --libs glib-2.0)\""
	@echo "  make MODE=debug run"
	@echo "  make bear"

# --- Include auto-generated dependency files ---
-include $(OBJECTS:.o=.d)
