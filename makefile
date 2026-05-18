# ==============================================================================
# colony_sim — Makefile
# ==============================================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
LDFLAGS :=

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

TARGET  := $(BIN_DIR)/colony_sim

# Collect all .c sources under src/ (colony_sim.c included)
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Headers under include/ — tracked as dependencies so a changed .h
# triggers recompilation of every translation unit that includes it
HDRS    := $(wildcard $(INC_DIR)/*.h)

# ==============================================================================

.PHONY: all clean release

all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@
	@echo ">>> Binary: $@"

# Compile each .c into a .o; create obj/ first if it does not exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output directories if they do not exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Optimised release build (enables -O2, disables assertions)
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Remove all generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo ">>> Clean complete."