#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_ARGS 100
#define MAX_COMMAND_LENGTH 1024
#define HISTORY_FILE "/.mysh_history"

void handle_sigchld();
void execute_command(char *command);
int is_builtin_command(char *command);
void execute_builtin_command(char *args[]);

void load_command_history();
void save_command_to_history(const char *command);
void show_history();

void execute_single_command(char *command);
void execute_with_input_redirection(char *command);
void execute_with_append_redirection(char *command);
void execute_with_redirection(char *command);
void execute_with_pipe(char *command);

#endif