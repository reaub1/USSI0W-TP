#include "mysh.h"

int main() {
    char command[MAX_COMMAND_LENGTH];
    signal(SIGCHLD, handle_sigchld);
    load_command_history();

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
    return 0;
}