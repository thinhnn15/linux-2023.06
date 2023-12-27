#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        // Add child process code here
        return 0;
    } else {
        // Parent process
        printf("Parent process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
    return 0;
}
