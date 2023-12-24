# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -pedantic

# Current directory
CUR_DIR := $(shell pwd)
# Binaries directory
BIN_DIR := $(CUR_DIR)/bin
# Source directory
SRC_DIR := $(CUR_DIR)/src
# Include directory
INC_DIR := $(CUR_DIR)/inc
# Object directory
OBJ_DIR := $(CUR_DIR)/obj
# Library directory
LIB_DIR := $(CUR_DIR)/lib

all:
	# Create the object file_system
	$(CC) $(CFLAGS) -c $(SRC_DIR)/file_system.c -o $(OBJ_DIR)/file_system.o -I$(INC_DIR)

	# Create the executable
	$(CC) $(CFLAGS) $(CUR_DIR)/main.c -o $(BIN_DIR)/file_system -I$(INC_DIR) $(OBJ_DIR)/file_system.o

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*
	rm -f $(LIB_DIR)/*
	rm -f $(CUR_DIR)/test.txt
