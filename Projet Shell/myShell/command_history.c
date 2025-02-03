#include "command_history.h"
#include "mysh.h"

void load_command_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) return;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
    }

    fclose(file);
}

void save_command_to_history(const char *command) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (!file) return;
    
    fprintf(file, "%s\n", command);
    fclose(file);
}

void show_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) {
        printf("Aucun historique disponible.\n");
        return;
    }

    char line[1024];
    int index = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d %s", index++, line);
    }

    fclose(file);
}