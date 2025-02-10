#include "execution.h"
#include "mysh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "builtin_commands.h"


void execute_single_command(char *command) {
    char *args[MAX_ARGS];
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
        return;
    } 

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        char *alias_value = get_alias_value(args[0]);

        if (alias_value != NULL) {
            printf("Exécution de l'alias : %s -> %s\n", args[0], alias_value);
            // Exécuter l'alias
            execvp(alias_value, args);  // Utilise execvp pour exécuter l'alias
        } else {
            // Si l'alias n'est pas trouvé, on exécute la commande normalement
            if (execvp(args[0], args) == -1) {
                perror("execvp");  // Affiche l'erreur si execvp échoue
                printf("Commande introuvable : %s\n", args[0]);  // Affiche un message d'erreur personnalisé
                exit(EXIT_FAILURE);  // Quitte avec un code d'erreur
            }
        }
    } else {
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("Processus en arrière-plan lancé avec PID %d\n", pid);
        }
    }
}

void execute_with_input_redirection(char *command) {
    char *cmd = strtok(command, "<");
    char *filename = strtok(NULL, "<");

    if (!cmd || !filename) {
        fprintf(stderr, "Erreur de syntaxe pour la redirection `<`\n");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd;
    if (strstr(command, "<<")) {
        // Mode heredoc
        printf("Heredoc (<<) non implémenté complètement\n");
        return;
    } else {
        // Mode simple <
        fd = open(filename, O_RDONLY);
    }

    if (fd == -1) {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
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
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        waitpid(pid, &status, 0);
    }
}

void execute_with_append_redirection(char *command) {
    char *cmd = strtok(command, ">>");
    char *filename = strtok(NULL, ">>");

    if (!cmd || !filename) {
        fprintf(stderr, "Erreur de syntaxe pour la redirection `>>`\n");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
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
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        waitpid(pid, &status, 0);
    }
}

void execute_with_redirection(char *command) {
    char *cmd = strtok(command, ">");
    char *filename = strtok(NULL, ">");

    //printf("redirection\n");
    //printf("cmd: %s\n", cmd);
    //printf("filename: %s\n", filename);

    if (!cmd || !filename) {
        fprintf(stderr, "Erreur de syntaxe pour la redirection `>`\n");
        return;
    }

    while (*filename == ' ') filename++;
    filename[strcspn(filename, " ")] = '\0';

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(fd);
        return;
    }

    if (pid == 0) {
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
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
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        close(fd);
        int status;
        waitpid(pid, &status, 0);
    }

    //printf("Vérification du fichier après exécution...\n");
    char buffer[1024];
    FILE *file = fopen(filename, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            //printf("%s", buffer);
        }
        fclose(file);
    } else {
        perror("fopen");
    }
}

void execute_with_pipe(char *command) {
    char *cmd1 = strtok(command, "|");
    char *cmd2 = strtok(NULL, "|");

    if (!cmd1 || !cmd2) {
        fprintf(stderr, "Erreur de syntaxe pour le pipe `|`\n");
        return;
    }

    while (*cmd2 == ' ') cmd2++;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return;
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execute_single_command(cmd1);
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return;
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execute_single_command(cmd2);
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void execute_with_logical_operators(char *command) {
    char *cmd1, *cmd2;

    if ((cmd1 = strtok(command, "&&"))) {
        cmd2 = strtok(NULL, "&&");

        //printf("cmd1: %s\n", cmd1);
        //printf("cmd2: %s\n", cmd2);

        execute_command(cmd1);
        if (cmd2) {
            execute_command(cmd2);
        }
        return; 
    }

    if ((cmd1 = strtok(command, "||"))) {
        cmd2 = strtok(NULL, "||");

        execute_command(cmd1);
        if (cmd2) {
            execute_command(cmd2);
        }
    }
}


void execute_command(char *command) {
    if (strstr(command, "&&") || strstr(command, "||")) {
        execute_with_logical_operators(command);
    } else if (strstr(command, " | ")) {
        execute_with_pipe(command);
    } else if (strstr(command, " < ")) {
        execute_with_input_redirection(command);
    } else if (strstr(command, " >> ")) {
        execute_with_append_redirection(command);
    } else if (strstr(command, " > ")) {
        execute_with_redirection(command);
    } else {
        execute_single_command(command);
    }
    save_command_to_history(command);
}