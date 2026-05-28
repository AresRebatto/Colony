# ==============================================================================
# colony_sim — Makefile
# ==============================================================================
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
LDFLAGS :=
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
ASM_DIR := asm
BIN_DIR := bin
TARGET  := $(BIN_DIR)/colony_sim
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
ASMS    := $(patsubst $(SRC_DIR)/%.c, $(ASM_DIR)/%.s, $(SRCS))
HDRS    := $(wildcard $(INC_DIR)/*.h)
# ==============================================================================
.PHONY: all clean release asm

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@
	@echo ">>> Binary: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate one .s per .c under asm/
$(ASM_DIR)/%.s: $(SRC_DIR)/%.c $(HDRS) | $(ASM_DIR)
	$(CC) $(CFLAGS) -S -fverbose-asm $< -o $@

# Compile .o directly from the .s files already in asm/
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s | $(OBJ_DIR)
	$(CC) -c $< -o $@

# asm: dump all translation units to .s, then link the final binary
asm: $(HDRS)
	mkdir -p $(ASM_DIR) $(OBJ_DIR) $(BIN_DIR)
	for f in $(SRCS); do \
		base=$$(basename $$f .c); \
		$(CC) $(CFLAGS) -S -fverbose-asm $$f -o $(ASM_DIR)/$$base.s; \
	done
	@echo ">>> Assembly files written to $(ASM_DIR)/"
	$(MAKE) $(TARGET) \
	        SRCS="$(ASMS)" \
	        OBJS="$(patsubst $(ASM_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASMS))"

release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(ASM_DIR) $(BIN_DIR)
	@echo ">>> Clean complete."
