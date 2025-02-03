#include "mysh.h"


void handle_sigchld() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void execute_builtin_command(char *args[]) {
    printf("execute_builtin_command\n");
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd");
        }
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd");
        }
    } else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
    }
    else if (strcmp(args[0], "history") == 0) {
        printf("history command detected\n");
        show_history();
    }
     else if (strcmp(args[0], "exit") == 0) {

        exit(0);
    }
    
}

int is_builtin_command(char *command) {
    char *builtins[] = {"cd", "pwd", "echo", "exit","history", NULL};
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            
            return 1;
        }
    }
    return 0;
}

int execute_single_command(char *command) {
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

    if (args[0] == NULL) return 0;

    printf("Executing: ");
    for (int j = 0; args[j] != NULL; j++) {
        printf("[%s] ", args[j]);
    }
    printf("\n");

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("Processus en arrière-plan lancé avec PID %d\n", pid);
        }
    }
    return 0;
}

void execute_command(char *command) {
    save_command_to_history(command);

    if (strstr(command, ">>")) {
        execute_with_append_redirection(command);
        return;
    }
    
    if (strchr(command, '<')) {
        execute_with_input_redirection(command);
        return;
    }

    if (strchr(command, '|')) {
        execute_with_pipe(command);
        return;
    }

    if (strchr(command, '>')) {
        execute_with_redirection(command);
        return;
    }

    char *args[MAX_ARGS];
    char *command_copy = strdup(command);
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    if (is_builtin_command(args[0])) {
        execute_builtin_command(args);
    } else {
        execute_single_command(command_copy);
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

void load_command_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) return;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
    }

    fclose(file);
}

void save_command_to_history(const char *command) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (!file) return;
    
    fprintf(file, "%s\n", command);
    fclose(file);
}

void show_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) {
        printf("Aucun historique disponible.\n");
        return;
    }

    char line[1024];
    int index = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d %s", index++, line);
    }

    fclose(file);
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    signal(SIGCHLD, handle_sigchld);
    load_command_history();

    while (1) {
        printf("my_sh> ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        execute_command(command);
    }
    return 0;
}