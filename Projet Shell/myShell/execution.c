#include "execution.h"
#include "mysh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"

void execute_single_command(char *command) {
    char *args[MAX_ARGS];
    char *command_copy = strdup(command);
    int i = 0;
    int background = 0;
    char *token = strtok(command, " \t");

    while (token != NULL && i < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0) {
            background = 1;
            break;
        }
        args[i++] = token;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    if (is_builtin_command(args[0])) {
        execute_builtin_command(args);
    } else {
        execute_single_command(command_copy);
    }

    free(command_copy);

    printf("Executing: ");
    for (int j = 0; args[j] != NULL; j++) {
        printf("[%s] ", args[j]);
    }
    printf("\n");

    pid_t pid = fork();
    if (pid == -1) {
        print_error("Échec du fork");
        return;
    }

    if (pid == 0) {
        execvp(args[0], args);
        print_error("Échec de l'exécution de la commande");
        exit(EXIT_FAILURE);
    } else {
        if (!background) {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                print_error("Échec de l'attente du processus");
            }
        } else {
            printf("Processus en arrière-plan lancé avec PID %d\n", pid);
        }
    }
}

void execute_with_input_redirection(char *command) {
    char *cmd = strtok(command, "<");
    char *filename = strtok(NULL, "<");

    if (!cmd || !filename) {
        print_syntax_error("redirection `<` incorrecte");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd;
    if (strstr(command, "<<")) {
        // Mode heredoc
        print_syntax_error("Mode heredoc (<<) non implémenté");
        return;
    } else {
        // Mode simple <
        fd = open(filename, O_RDONLY);
    }

    if (fd == -1) {
        print_error("Impossible d'ouvrir le fichier en écriture");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        print_error("Échec du fork");
        close(fd);
        return;
    }

    if (pid == 0) {
        dup2(fd, STDIN_FILENO);
        close(fd);

        char *args[MAX_ARGS];
        char *token = strtok(cmd, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);
        print_error("Échec de l'exécution de la commande");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            print_error("Échec de l'attente du processus");
        }
    }
}

void execute_with_append_redirection(char *command) {
    char *cmd = strtok(command, ">>");
    char *filename = strtok(NULL, ">>");

    if (!cmd || !filename) {
        print_syntax_error("redirection `>>` incorrecte");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        print_error("Impossible d'ouvrir le fichier en écriture");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        print_error("Échec du fork");
        close(fd);
        return;
    }

    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);

        char *args[MAX_ARGS];
        char *token = strtok(cmd, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);
        print_error("Échec de l'exécution de la commande");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            print_error("Échec de l'attente du processus");
        }
    }
}

void execute_with_redirection(char *command) {
    char *cmd = strtok(command, ">");
    char *filename = strtok(NULL, ">");

    if (!cmd || !filename) {
        print_syntax_error("redirection `>` incorrecte");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        print_error("Impossible d'ouvrir le fichier en écriture");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        print_error("Échec du fork");
        close(fd);
        return;
    }

    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);

        char *args[MAX_ARGS];
        char *token = strtok(cmd, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);
        print_error("Échec de l'exécution de la commande");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            print_error("Échec de l'attente du processus");
        }
    }
}

void execute_with_pipe(char *command) {
    char *cmd1 = strtok(command, "|");
    char *cmd2 = strtok(NULL, "|");

    if (!cmd1 || !cmd2) {
        print_syntax_error("pipe `|` incorrect");
        return;
    }

    while (*cmd2 == ' ') cmd2++;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        print_error("Échec de la création du pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        print_error("Échec du fork");
        return;
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            print_error("Échec de la redirection du stdout vers le pipe");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        execute_single_command(cmd1);
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        print_error("Échec du fork");
        return;
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            print_error("Échec de la redirection du stdin depuis le pipe");
            exit(EXIT_FAILURE);
        }
        
        close(pipefd[0]);

        execute_single_command(cmd2);
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    if (waitpid(pid1, NULL, 0) == -1) {
        print_error("Échec de l'attente du premier processus");
    }
    if (waitpid(pid2, NULL, 0) == -1) {
        print_error("Échec de l'attente du second processus");
    }
}

void execute_command(char *command) {
    if (strstr(command, "<")) {
        execute_with_input_redirection(command);
    } else if (strstr(command, ">>")) {
        execute_with_append_redirection(command);
    } else if (strstr(command, ">")) {
        execute_with_redirection(command);
    } else if (strstr(command, "|")) {
        execute_with_pipe(command);
    } else {
        execute_single_command(command);
    }
}