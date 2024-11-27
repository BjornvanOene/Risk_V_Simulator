# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -O2 -target arm64-apple-macos11

# Directories
SRC_DIR = .
BIN_DIR = bin
TEST_DIR = tests

# Source and header files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))
HEADERS = $(wildcard $(SRC_DIR)/*.h)

# Output binary
TARGET = ./main

# Default target
all: $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build target
$(TARGET): $(BIN_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compile source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

# Run tests (placeholder command; update based on your test framework)
test: all
	$(TEST_DIR)/run_tests.sh

.PHONY: all clean test
