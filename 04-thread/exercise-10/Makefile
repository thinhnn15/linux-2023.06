# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pthread

# Target executable
TARGET = exercise-10

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET) output.txt
