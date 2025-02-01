#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

void start_main_program() {
    printf("Main program started\n");
}

void finish_main_program() {
    printf("Main program finished\n");
}

void execute_builtin_command(char *args[]) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd");
        }
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd");
        }
    } else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
    } else if (strcmp(args[0], "exit") == 0) {

        exit(0);
    }
}

int is_builtin_command(char *command) {
    return strcmp(command, "cd") == 0 || strcmp(command, "pwd") == 0 ||
           strcmp(command, "echo") == 0 || strcmp(command, "exit") == 0;
}

int execute_single_command(char *command) {
    char *args[MAX_ARGS];
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return 0;

    if (is_builtin_command(args[0])) {
        execute_builtin_command(args);
        return 0;
    } else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return -1;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
            return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        }
    }
}

void execute_command(char *command) {
    char *subcommands[MAX_ARGS];
    int count = 0;
    int exit_status = 0;
    
    char *token = strtok(command, "&&");
    while (token != NULL && count < MAX_ARGS - 1) {
        subcommands[count++] = token;
        token = strtok(NULL, "&&");
    }
    subcommands[count] = NULL;

    if (count > 1) {
        for (int i = 0; i < count; i++) {
            exit_status = execute_single_command(subcommands[i]);
            if (exit_status != 0) {
                return;
            }
        }
        return;
    }

    count = 0;
    token = strtok(command, "||");
    while (token != NULL && count < MAX_ARGS - 1) {
        subcommands[count++] = token;
        token = strtok(NULL, "||");
    }
    subcommands[count] = NULL;

    if (count > 1) {
        for (int i = 0; i < count; i++) {
            exit_status = execute_single_command(subcommands[i]);
            if (exit_status == 0) {
                return;
            }
        }
        return;
    }

    execute_single_command(command);
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    start_main_program();

    while (1) {
        printf("my_sh> ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        execute_command(command);
    }

    finish_main_program();
    return 0;
}