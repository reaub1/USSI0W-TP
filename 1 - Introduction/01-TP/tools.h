#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

typedef struct {
    int file; 
    char mode;
    char buffer[1024];
    int index;
}FICHIER;

void copyFile(char* src, char* dest);
void reverse(char* src);
void ls(char* src);
FICHIER my_open(const char *path, const char *mode);
char my_getc(FICHIER file);
char my_putc(char c, FICHIER file);
void my_close(FICHIER file);