# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -O2
DEBUG_FLAGS = -Wall -Wextra -g
TARGET_MACOS = -target arm64-apple-macos11
TARGET_WINDOWS = -target x86_64-windows-gnu
TARGET_LINUX = -target x86_64-linux-gnu

# Directories
SRC_DIR = .
BIN_DIR = bin
TEST_DIR = tests

# Source and header files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))
HEADERS = $(wildcard $(SRC_DIR)/*.h)

# Output binaries
TARGET = ./main
TARGET_WINDOWS_BINARY = main.exe
TARGET_LINUX_BINARY = main_linux
DEBUG_BINARY = ./main_debug

# Default target
all: $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build macOS target
$(TARGET): $(BIN_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(TARGET_MACOS) -o $@ $(OBJ_FILES)

# Compile source files into object files for macOS
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(TARGET_MACOS) -c $< -o $@

# Build Windows target
windows: $(BIN_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(TARGET_WINDOWS) -o $(TARGET_WINDOWS_BINARY) $(OBJ_FILES)

# Build Linux target
linux: $(BIN_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(TARGET_LINUX) -o $(TARGET_LINUX_BINARY) $(OBJ_FILES)

# Debug target for macOS
debug: $(BIN_DIR) $(OBJ_FILES)
	$(CC) $(DEBUG_FLAGS) $(TARGET_MACOS) -o $(DEBUG_BINARY) $(OBJ_FILES)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR) $(TARGET) $(TARGET_WINDOWS_BINARY) $(TARGET_LINUX_BINARY) $(DEBUG_BINARY)

# Run tests (placeholder command; update based on your test framework)
test: all
	$(TEST_DIR)/run_tests.sh

.PHONY: all clean test windows linux debug
