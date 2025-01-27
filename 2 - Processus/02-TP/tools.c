#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void forkYourself() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Processus fils : PID = %d, PPID = %d\n", getpid(), getppid());
        int exit_code = getpid() % 10;
        printf("Fils se termine avec le code de retour : %d\n", exit_code);
        exit(exit_code);
    } else {
        int status;
        wait(&status);
        printf("Processus père : PID fils = %d\n", pid);

        if (WIFEXITED(status)) {
            printf("Le fils s'est terminé avec le code de retour : %d\n", WEXITSTATUS(status));
        } else {
            printf("Le fils ne s'est pas terminé correctement.\n");
        }
    }
}

void redirectionStandard(const char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Fils PID : %d\n", getpid());

        close(STDOUT_FILENO);

        char tempFile[] = "/tmp/proc-exercise";
        int fileDesc = mkstemp(tempFile);
        if (fileDesc == -1) {
            perror("Erreur lors de la création du fichier temporaire");
            exit(EXIT_FAILURE);
        }

        if (dup2(fileDesc, STDOUT_FILENO) == -1) {
            perror("Erreur lors de dup2");
            exit(EXIT_FAILURE);
        }

        printf("Descripteur de fichier ouvert : %d\n", fileDesc);

        execlp(command, command, NULL);

        perror("Erreur lors de exec");
        exit(EXIT_FAILURE);
    } else {
        printf("Père PID : %d\n", getpid());
        int status;

        wait(&status);

        if (WIFEXITED(status)) {
            printf("Le fils s'est terminé avec le code de retour : %d\n", WEXITSTATUS(status));
        } else {
            printf("Le fils ne s'est pas terminé correctement.\n");
        }

        printf("That's All Folks!\n");
    }
}

void redirectionPipe(void) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Erreur lors de fork pour ps");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);

        execlp("ps", "ps", "eaux", NULL);
        perror("Erreur lors de exec pour ps");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Erreur lors de fork pour grep");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);

        execlp("grep", "grep", "^root", NULL);
        perror("Erreur lors de exec pour grep");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    if (WIFEXITED(status1) && WIFEXITED(status2)) {
        write(STDOUT_FILENO, "root est connecté\n", 18);
    } else {
        write(STDOUT_FILENO, "Erreur lors de l'exécution des processus fils\n", 46);
    }
}