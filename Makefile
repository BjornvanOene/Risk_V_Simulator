# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -std=c11

# Directory paths
SRC_DIR = .
BIN_DIR = bin

# Source files (list all .c files)
SRC_FILES = btype.c decoder.c itype.c jtype.c main.c readbin.c regs.c rtype.c stype.c utype.c

# Output executable
OUTPUT = $(BIN_DIR)/main

# Default target
all: $(OUTPUT)

# Compile all source files into the final executable
$(OUTPUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(OUTPUT)

# Clean the bin directory (remove the executable)
clean:
	rm -f $(OUTPUT)

# Phony targets (to avoid conflict with files named 'all' or 'clean')
.PHONY: all clean
