/**
 * @file command_history.c
 * @brief Implémentation de la commande history
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#include "command_history.h"
#include "mysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Retourne le chemin du fichier d'historique
 * @return char* chemin du fichier d'historique
 */
char *get_history_path() {
    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Erreur : Impossible de trouver HOME\n");
        return NULL;
    }

    size_t path_len = strlen(home) + strlen(HISTORY_FILE) + 1;
    char *history_path = malloc(path_len);
    if (!history_path) {
        perror("malloc");
        return NULL;
    }

    snprintf(history_path, path_len, "%s%s", home, HISTORY_FILE);

    return history_path;
}
#include <errno.h>
#include "utils.h"

/**
 * @brief Charge l'historique des commandes depuis le fichier
 * @return void
 */
void load_command_history() {
    char *history_file = get_history_path();
    if (!history_file) return;
    
    FILE *file = fopen(history_file, "r");
    free(history_file);
    if (!file) {
        print_error("Impossible d'ouvrir le fichier d'historique en lecture");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
    }

    if (fclose(file) != 0) {
        print_error("Erreur lors de la fermeture du fichier d'historique");
    }
}

/**
 * @brief Sauvegarde une commande dans l'historique
 * @param command commande à sauvegarder
 * @return void
 */
void save_command_to_history(const char *command) {
    char *history_file = get_history_path();
    if (!history_file) return;
    
    FILE *file = fopen(history_file, "a");
    if (!file) {
        print_error("Impossible de sauvegarder dans l'historique");
        {
        free(history_file);
        return;
    }

    //printf("command writed");
    }
    
    if (fprintf(file, "%s\n", command) < 0) {
        print_error("Erreur lors de l'écriture dans le fichier d'historique");
    }

    if (fclose(file) != 0) {
        print_error("Erreur lors de la fermeture du fichier d'historique");
    }
    free(history_file);
}

/**
 * @brief Affiche l'historique des commandes
 * @return void
 */
void show_history() {
    char *history_file = get_history_path();
    if (!history_file) return;
    
    FILE *file = fopen(history_file, "r");

    free(history_file);
    if (!file) {
        print_error("Aucun historique disponible");
        return;
    }

    char line[1024];
    int index = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d %s", index++, line);
    }

    if (fclose(file) != 0) {
        print_error("Erreur lors de la fermeture du fichier d'historique");
    }
}
