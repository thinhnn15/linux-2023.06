#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_THREADS 2

void* threadFunction(void* arg) {
    for(int i = 0; i < *(int*)arg; i++) {
        int fd = open("output.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd != -1) {
            char buffer = 'A';
            write(fd, &buffer, sizeof(buffer));
            close(fd);
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int numberCharacters = 50000;
    // int numberCharacters = 100000;

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, threadFunction, &numberCharacters);

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("All threads have finished\n");

    return 0;
}
