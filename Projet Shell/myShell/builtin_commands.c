#include "builtin_commands.h"
#include "mysh.h"
#include "utils.h"
#include <errno.h>
#include "command_history.h"

void execute_builtin_command(char *args[]) {
    if (strcmp(args[0], "cd") == 0) {

        //printf("args1 : %s\n", args[1]);

        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            print_error("Échec de la commande cd");
        }
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            print_error("Impossible d'obtenir le répertoire courant");
        }
    } else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s \n", args[i]);
        }
    }
    else if (strcmp(args[0], "history") == 0) {
        printf("history command detected\n");
        show_history();
    }
    else if (strcmp(args[0], "exit") == 0) {
        if (args[1] != NULL) {
            print_error("exit ne prend pas d'arguments");
        }
        exit(0);
    }
    else if (strcmp(args[0], "man") == 0) {
        if (args[1] == NULL) {
            print_error("Veuillez spécifier une page de manuel. Essayez 'man my_sh'.");
            return;
        }
        if (strcmp(args[1], "my_sh") == 0) {
            printf("\n=== Manuel de MyShell ===\n");
            printf("my_sh - Un mini-shell personnalisé pour exécuter des commandes Unix.\n\n");
            printf("DESCRIPTION\n");
            printf("  Un interpréteur de commandes simple, similaire à Bash.\n");
            printf("  Permet d'exécuter des commandes Unix standard avec redirections et pipes.\n\n");
            printf("COMMANDES INTERNES\n");
            printf("  ls               : Affiche le contenu du répertoire courant.\n");
            printf("  cd [répertoire]  : Change le répertoire courant.\n");
            printf("  pwd              : Affiche le chemin du répertoire courant.\n");
            printf("  echo [texte]     : Affiche du texte à l'écran.\n");
            printf("  history          : Affiche l'historique des commande précédentes.\n");
            printf("  exit             : Quitte le shell.\n\n");
            printf("EXEMPLES\n");
            printf("  my_sh> man my_sh         # Affiche cette aide\n");
            printf("  my_sh> ls > fichier.txt  # Redirige ls vers un fichier\n\n");
            return;
        } else {
            print_error("Commande man inconnue. Essayez 'man my_sh'.");
            return;
        }
    }
    
}

int is_builtin_command(char *command) {
    char *builtins[] = {"cd", "pwd", "echo", "exit", "history", "man", NULL};
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            return 1;
        }
    }
    return 0;
}