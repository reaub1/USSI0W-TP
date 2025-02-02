#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

void execute_builtin_command(char *args[]);
int is_builtin_command(char *command);
int execute_single_command(char *command);
void execute_command(char *command);
void execute_with_redirection(char *command);
void execute_with_pipe(char *command);
void execute_with_append_redirection(char *command);
void execute_with_input_redirection(char *command);


#endif