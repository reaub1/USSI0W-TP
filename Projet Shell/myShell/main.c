#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

void start_main_program() {
    printf("Main program started\n");
}

void finish_main_program() {
    printf("Main program finished\n");
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

        if (strcmp(command, "exit") == 0) {
            break;
        }

        printf("Commande reçue : %s\n", command);
    }

    finish_main_program();
    return 0;
}