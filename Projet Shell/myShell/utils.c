#include "utils.h"
#include <sys/wait.h>
#include <stddef.h>

void handle_sigchld() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}