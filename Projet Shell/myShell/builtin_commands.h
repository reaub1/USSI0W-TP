/**
 * @file builtin_commands.h
 * @brief Header des commandes intégrées
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

#include "typedef.h"

void show_aliases();
void remove_alias(char *name);
void add_alias(char *name, char *value);
char *get_alias_value(char *name);

void execute_builtin_command(char *args[]);
int is_builtin_command(char *command);

#endif