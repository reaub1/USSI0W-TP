#include "utils.h"
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void print_error(const char *msg) {
    if (errno != 0) {
        fprintf(stderr, "ERR : %s - %s\n", msg, strerror(errno));
    } else {
        fprintf(stderr, "ERR : %s\n", msg);
    }
}

void print_syntax_error(const char *msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}

void handle_sigchld() {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        if (errno != ECHILD) {
            print_error("Erreur lors de la gestion des processus zombies");
        }
    }
}