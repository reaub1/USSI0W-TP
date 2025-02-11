/**
 * @file utils.h
 * @brief Header des méthodes outils
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */


#ifndef UTILS_H
#define UTILS_H

void handle_sigchld();
void print_error(const char *msg);
void print_syntax_error(const char *msg);
#endif