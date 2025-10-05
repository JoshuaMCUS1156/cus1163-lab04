#include "executor.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int execute_command(char *command, char **args) {
    // TODO 1: Fork the child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    // TODO 2: Child process - execute the command
    if (pid == 0) {
        execvp(command, args);
        // If we reach here, execvp failed
        perror("execvp");
        exit(1);  // must use exit, not return
    }

    // TODO 3: Parent process - wait for child
    int status;
    pid_t wpid = waitpid(pid, &status, 0);
    if (wpid == -1) {
        perror("waitpid");
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        return -1;
    }
}
