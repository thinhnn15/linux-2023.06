#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "file_system.h"
// Function to read the content of a file
char* read_file(const char* filepath) {
    // Use linux file system API to open file
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return NULL;
    }
    // Seek to start of file
    lseek(fd, 0, SEEK_SET);
    // Get the size of file
    int file_size = lseek(fd, 0, SEEK_END);
    // Seek to start of file
    lseek(fd, 0, SEEK_SET);
    // Allocate memory for content
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        perror("Error allocating memory");
        close(fd);
        return NULL;
    }
    // Read content from file
    int numb_read = read(fd, content, file_size);
    if (numb_read == -1) {
        perror("Error reading file");
        close(fd);
        return NULL;
    }
    // Close file
    close(fd);
    // Add null terminator to content
    content[file_size] = '\0';

    return content;
}

// Function to write content to a file
int write_file(const char* filepath, const char* content) {
    // Use linux file system API to open file
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    // Seek to start of file
    lseek(fd, 0, SEEK_SET);
    // write content to file from seek position
    int numb_read = write(fd, content, strlen(content));
    if (numb_read == -1) {
        perror("Error writing file");
        return -1;
    }
    // Close file
    close(fd);

    return 0;
}

// Function to append content to a file
int append_file(const char* filepath, const char* content, int seek_pos) {
    // Call Linux file system to open file, with O_APPEND flag
    int fd = open(filepath, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    // Seek to start of file
    lseek(fd, seek_pos, SEEK_SET);
    // write content to file from seek position
    int numb_read = write(fd, content, strlen(content));
    if (numb_read == -1) {
        perror("Error writing file");
        return -1;
    }
    // Close file
    close(fd);

    return 0;
}



// Function to get the content of a file
void get_content(const char* filepath) {
    char* content = read_file(filepath);
    if (content != NULL) {
        printf("Content of file %s:\n%s\n", filepath, content);
        free(content);
    }
}

// Function to get the stat of a file
void get_stat(const char* filepath) {
    struct stat file_stat;
    if (stat(filepath, &file_stat) == 0) {
        printf("File: %s\n", filepath);
        printf("Size: %ld bytes\n", file_stat.st_size);
        printf("Permissions: %o\n", file_stat.st_mode & 0777);
        printf("Last modified: %s", ctime(&file_stat.st_mtime));
    } else {
        perror("Error getting file stat");
    }
}