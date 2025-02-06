#include "builtin_commands.h"
#include "mysh.h"
#include "command_history.h"

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
        printf( "End of the echo \n");
    }
    else if (strcmp(args[0], "history") == 0) {
        printf("history command detected\n");
        show_history();
    }
    else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
}

int is_builtin_command(char *command) {
    char *builtins[] = {"cd", "pwd", "echo", "exit", "history", NULL};
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            return 1;
        }
    }
    return 0;
}