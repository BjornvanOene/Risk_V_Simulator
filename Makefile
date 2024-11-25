# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = main

# Source file
SRC = main.c

# Default rule to build the target
all: $(TARGET)

# Compile source file directly into the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
