#include "command_history.h"
#include "mysh.h"
#include <errno.h>
#include "utils.h"

void load_command_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
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

void save_command_to_history(const char *command) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (!file) {
        print_error("Impossible de sauvegarder dans l'historique");
        return;
    }
    
    if (fprintf(file, "%s\n", command) < 0) {
        print_error("Erreur lors de l'écriture dans le fichier d'historique");
    }

    if (fclose(file) != 0) {
        print_error("Erreur lors de la fermeture du fichier d'historique");
    }
}

void show_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
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