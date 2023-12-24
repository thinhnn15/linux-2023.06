#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function to read the content of a file
char* read_file(const char* filepath);

// Function to write content to a file
int write_file(const char* filepath, const char* content);

// Function to append content to a file
int append_file(const char* filepath, const char* content, int seek_pos);

// Function to get the content of a file
void get_content(const char* filepath);

// Function to get the stat of a file
void get_stat(const char* filepath);
