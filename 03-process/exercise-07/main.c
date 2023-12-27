#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void completeChildProcess() {
    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        printf("Child process exited with status: %d\n", WEXITSTATUS(status));
    } else {
        printf("Child process terminated abnormally\n");
    }
}
int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        // Sleep for 5 seconds
        sleep(5);
    } else {
        // Parent process
        printf("Parent process: PID = %d, PPID = %d\n", getpid(), getppid());
        // Add parent process logic here
        signal(SIGCHLD , completeChildProcess);
        // end of parent process logic
        printf("End of parent process\n");
        for(;;){} // infinite loop (to keep the process running
    }

    return 0;
}
