#include "mysh.h"

int main(int argc, char *argv[]) {
    char command[MAX_COMMAND_LENGTH];
    signal(SIGCHLD, handle_sigchld);
    load_command_history();

    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        execute_command(argv[2]);
        return 0;
    }

    while (1) {
        printf("my_sh> ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            if (ferror(stdin)) {
                print_error("Erreur de lecture de la commande");
            }
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