/**
 * @file builtin_commands.c
 * @brief Implémentation des commandes intégrées
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#include "builtin_commands.h"
#include "mysh.h"
#include "utils.h"
#include <errno.h>
#include "command_history.h"

int alias_count = 0;


/**
 * @brief Affiche la liste des alias
 * @param void
 */
void show_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
    }
}

/**
 * @brief Supprimer un allias
 * @param name nom de l'allias
 * @return void
 */

void remove_alias(char *name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
            for (int j = i; j < alias_count - 1; j++) {
                alias_list[j] = alias_list[j + 1];
            }
            alias_count--;
            return;
        }
    }
    printf("Alias introuvable : %s\n", name);
}

/**
 * @brief Retourne la valeur de l'alias
 * @param name nom de l'allias
 * @return char valeur de l'allias
 */
char *get_alias_value(char *name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
            return alias_list[i].value;
        }
    }
    return NULL;
}

/**
 * @brief Création d'un alias
 * @param name nom de l'allias
 * @param value valeur de l'allias
 * @return void
 */
void add_alias(char *name, char *value) {

    //printf("add_alias\n");

    if (alias_count >= MAX_ALIASES) {
        printf("Nombre maximal d'alias atteint !\n");
        return;
    }
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
           


            strcpy(alias_list[i].value, value);
            return;
        }
    }
    // Ajout d'un nouvel alias
    // Mise à jour si l'alias existe déjà
            //printf("Mise à jour de l'alias %s\n", name);
            
            //printf("name : %s\n", name);
            //printf("value : %s\n", value);

    strcpy(alias_list[alias_count].name, name);
    strcpy(alias_list[alias_count].value, value);
    alias_count++;
}

/**
 * @brief Exectution des commandes intégrées
 * @param args tableau des arguments
 * @return void
 */
void execute_builtin_command(char *args[]) {
    if (strcmp(args[0], "alias") == 0) {
        //printf("alias detected : %s\n", args[0]);
        if (args[1] == NULL) {
            show_aliases();
        } else {
             char *equal_pos = strchr(args[1], '=');
            if (!equal_pos) {
                printf("Usage: alias name='command'\n");
                return;
            }

            // Extraire `name`
            *equal_pos = '\0';  
            char *name = args[1];

            // Stocker `value` dans un buffer sécurisé
            char value[1024] = {0};  
            snprintf(value, sizeof(value), "%s", equal_pos + 1); 

            // Concaténer `args[2]`, `args[3]`, etc.
            for (int i = 2; args[i] != NULL; i++) {
                strncat(value, " ", sizeof(value) - strlen(value) - 1);
                strncat(value, args[i], sizeof(value) - strlen(value) - 1);
            }

            // Suppression des guillemets si présents
            size_t len = strlen(value);
            if (len > 1 && value[0] == '"' && value[len - 1] == '"') {
                memmove(value, value + 1, len - 2);
                value[len - 2] = '\0';
            }

            if (name[0] != '\0' && value[0] != '\0') {
                add_alias(name, value);
            } else {
                printf("Erreur : alias invalide\n");
            }
        }
    } else if (strcmp(args[0], "unalias") == 0) {
        if (args[1] == NULL) {
            printf("Usage: unalias nom\n");
        } else {
            remove_alias(args[1]);
        }
    } 
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
        //printf("history command detected\n");
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

/**
 * @brief Vérifie si la commande est intégrée
 * @param command commande à vérifier
 * @return int 1 si la commande est intégrée, 0 sinon
 */
int is_builtin_command(char *command) {
    char *builtins[] = {"cd", "pwd", "echo", "exit", "history", "man","alias", NULL};
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
