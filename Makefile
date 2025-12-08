# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude

# Folders
SRC_DIR := src
BUILD_DIR := build

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

TARGET := $(BUILD_DIR)/main

# Standard-Target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(BUILD_DIR)

# run
run: all
	./$(TARGET)
