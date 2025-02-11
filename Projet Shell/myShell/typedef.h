/**
 * @file typedef.h
 * @brief Fichier de définition
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIASES 100

typedef struct {
    char name[50];
    char value[256];
} Alias;

Alias alias_list[MAX_ALIASES];
extern int alias_count;