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
# Static library directory
STATIC_LIB_DIR := $(LIB_DIR)/static
# Shared library directory
SHARED_LIB_DIR := $(LIB_DIR)/shared

static: 
	# Create the object files
	$(CC) $(CFLAGS) -c $(SRC_DIR)/hello.c -o $(OBJ_DIR)/libHello.o -I$(INC_DIR)

	# Create the static library
	ar rcs $(STATIC_LIB_DIR)/libHello.a $(OBJ_DIR)/libHello.o

	# Create the executable
	$(CC) $(CFLAGS) $(CUR_DIR)/main.c -o $(BIN_DIR)/hello-static -I$(INC_DIR) -L$(STATIC_LIB_DIR) -lHello
shared:
	# Create the object files
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/hello.c -o $(OBJ_DIR)/libHello.o -I$(INC_DIR)

	# Create the shared library
	$(CC) $(CFLAGS) -shared -o $(SHARED_LIB_DIR)/libHello.so $(OBJ_DIR)/libHello.o

	# Install .so file to /usr/lib
	sudo cp $(SHARED_LIB_DIR)/libHello.so /usr/lib

	# Create the executable
	$(CC) $(CFLAGS) $(CUR_DIR)/main.c -o $(BIN_DIR)/hello-shared -I$(INC_DIR) -L$(SHARED_LIB_DIR) -lHello
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*
	rm -f $(STATIC_LIB_DIR)/*
	rm -f $(SHARED_LIB_DIR)/*