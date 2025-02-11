/**
 * @file command_history.h
 * @brief Header de la commande history
 * @author PICHON Sébastien, BECHLEM Robin
 * @date 2025-02-11
 */

#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

void load_command_history();
void save_command_to_history(const char *command);
void show_history();

#endif