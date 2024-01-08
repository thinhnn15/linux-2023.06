#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 2

struct human {
    char name[50];
    char phone_number[20];
    char country[50];
};

void* threadFunction(void* arg) {
    if (arg != NULL) {
        struct human* person = (struct human*)arg;
        printf("Person Information:\n");
        printf("Name: %s\n", person->name);
        printf("Phone Number: %s\n", person->phone_number);
        printf("Country: %s\n", person->country);
    }
    else {
        printf("No argument passed to threadFunction\n");
    }
    printf("Exiting threadFunction\n");  // Added printf
    return NULL;
}


int main() {
    pthread_t threads[NUM_THREADS];

    // Create multiple threads
    struct human person;
    strcpy(person.name, "John Doe");
    strcpy(person.phone_number, "1234567890");
    strcpy(person.country, "USA");

    for (int i = 0; i < NUM_THREADS; i++) {
        void* threadArg = NULL;
        if (i == 1) {
            threadArg = &person;
        }
        pthread_create(&threads[i], NULL, threadFunction, threadArg);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed\n");

    return 0;
}
