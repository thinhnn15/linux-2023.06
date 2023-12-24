#include <stdio.h>
#include "file_system.h"

int main() {
    // Create new file test.txt
    write_file("test.txt", "Hello, world!\n");

    // Read the content of test.txt
    get_content("test.txt");

    // Get the stat of test.txt
    get_stat("test.txt");
    // Append content to test.txt
    append_file("test.txt", "***", 0);
    // Read the content of test.txt
    get_content("test.txt");

    // Get the stat of test.txt
    get_stat("test.txt");
    
    return 0;
}
