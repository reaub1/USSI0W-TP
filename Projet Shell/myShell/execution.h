#ifndef EXECUTION_H
#define EXECUTION_H

void execute_single_command(char *command);
void execute_with_input_redirection(char *command);
void execute_with_append_redirection(char *command);
void execute_with_redirection(char *command);
void execute_with_pipe(char *command);
void execute_with_logical_operators(char *command);
void execute_command(char *command);

#endif