# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iheaders -g
LDFLAGS =

# Directories
SRC_DIR = headers
BIN_DIR = bin

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c) main.c

# Output binary
TARGET = $(BIN_DIR)/main

# Tasks
.PHONY: all clean run tests

# Default target
all: $(BIN_DIR) $(TARGET)

# Create the binary directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile and link the target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Run the program
run: $(TARGET)
	$(TARGET)

# Clean the build
clean:
	rm -rf $(BIN_DIR)

# Run tests
tests: $(TARGET)
	@echo "Running tests..."
	# Add your test commands here, e.g., executing binary with test inputs
	@echo "Tests completed."
