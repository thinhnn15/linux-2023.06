#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 3

struct Student {
    char name[50];
    char dateOfBirth[20];
    char country[50];
};

enum eMutex {
    MUTEX_THREAD,
    MUTEX_FILE,
    MUTEX_MAX
};

pthread_mutex_t mutex[MUTEX_MAX] = {PTHREAD_MUTEX_INITIALIZER};

bool threadReady[NUM_THREADS] = {false};
pthread_cond_t cond[NUM_THREADS] = {PTHREAD_COND_INITIALIZER};

struct Student g_student;
// add bool atomic g_exit 
bool g_exit = false;

void* threadInputStudentInfo(void* arg) {
    (void)arg;
    // Loop for getting student info
    while (true) {
        // Wait for thread 1 to be ready
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        while (!threadReady[0]) {
            pthread_cond_wait(&cond[0], &mutex[MUTEX_THREAD]);
        }
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);
        struct Student student;
        printf("Enter student name (or 'q' to quit): ");
        scanf("%s", student.name);

        if (strcmp(student.name, "q") == 0) {
            g_exit = true;
            printf("Exit program in thread input\n");
            threadReady[1] = true;
            threadReady[2] = true;
            pthread_cond_signal(&cond[1]);
            pthread_cond_signal(&cond[2]);
            break;
        }

        printf("Enter student date of birth: ");
        scanf("%s", student.dateOfBirth);

        printf("Enter student country: ");
        scanf("%s", student.country);

        // Notify thread 2 to continue
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        threadReady[0] = false;
        g_student = student;
        threadReady[1] = true;
        pthread_cond_signal(&cond[1]);
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);
    }
    return NULL;
}
void* threadWriteStudentInfo(void* arg)
{
    (void)arg;
    // Loop for writing student info to file
    while (true) {
        // Wait for thread 2 to be ready
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        while (!threadReady[1]) {
            pthread_cond_wait(&cond[1], &mutex[MUTEX_THREAD]);
        }
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);

        if (g_exit) {
            printf("Exit program in thread write\n");
            break; // Exit the loop if 'q' is entered
        }

        pthread_mutex_lock(&mutex[MUTEX_FILE]);
        FILE* file = fopen("output.txt", "a"); // Open file in append mode
        if (file == NULL) {
            printf("Error opening file\n");
            return NULL;
        }

        fprintf(file, "Name: %s\n", g_student.name);
        fprintf(file, "Date of Birth: %s\n", g_student.dateOfBirth);
        fprintf(file, "Country: %s\n", g_student.country);

        fclose(file);
        pthread_mutex_unlock(&mutex[MUTEX_FILE]);
        threadReady[1] = false;
        // Notify thread 3 to continue
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        threadReady[2] = true;
        pthread_cond_signal(&cond[2]);
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);
    }
    return NULL;
}
void* threadReadStudentInfo(void* arg){
    (void)arg;
    // Wait for thread 3 to be ready
    while(true){
        // Show for user see this is info of student
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        while (!threadReady[2])
        {
            pthread_cond_wait(&cond[2], &mutex[MUTEX_THREAD]);
        }
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);
        // check exit
        if (g_exit)
        {
            printf("Exit program in thread read\n");
            break; // Exit the loop if 'q' is entered
        }

        printf("/////////////////////////////////\n");
        printf("PRINT STUDENTS INFORMATION: START\n");
        printf("/////////////////////////////////\n");
        // Read student info from file
        FILE *file = fopen("output.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file\n");
            return NULL;
        }

        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }

        fclose(file);

        // Notify thread 1 to continue
        pthread_mutex_lock(&mutex[MUTEX_THREAD]);
        threadReady[2] = false;
        threadReady[0] = true;
        pthread_cond_signal(&cond[0]);
        pthread_mutex_unlock(&mutex[MUTEX_THREAD]);
        
        printf("/////////////////////////////////\n");
        printf("PRINT STUDENTS INFORMATION: END\n");
        printf("/////////////////////////////////\n");
    }
    
    return NULL;
}

typedef void* (*ThreadFunction)(void*);

ThreadFunction threadFunctions[NUM_THREADS] = {
    threadInputStudentInfo,
    threadWriteStudentInfo,
    threadReadStudentInfo
};

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threadFunctions[i], NULL);
    }

    pthread_mutex_lock(&mutex[MUTEX_THREAD]);
    threadReady[0] = true;
    pthread_cond_signal(&cond[0]);
    pthread_mutex_unlock(&mutex[MUTEX_THREAD]);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed\n");

    return 0;
}
