/**
 * @file utils.c
 * @brief Implémentation des méthodes outils
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#include "utils.h"
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * @brief Affiche un message d'erreur
 * @param msg message d'erreur
 * @return void
 */
void print_error(const char *msg) {
    if (errno != 0) {
        fprintf(stderr, "ERR : %s - %s\n", msg, strerror(errno));
    } else {
        fprintf(stderr, "ERR : %s\n", msg);
    }
}

/**
 * @brief Affiche un message d'erreur de syntaxe
 * @param msg message d'erreur
 * @return void
 */
void print_syntax_error(const char *msg) {
    fprintf(stderr, "Erreur de syntaxe : %s\n", msg);
}

/**
 * @brief Gestion des processus zombies
 * @return void
 */
void handle_sigchld() {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        if (errno != ECHILD) {
            print_error("Erreur lors de la gestion des processus zombies");
        }
    }
}