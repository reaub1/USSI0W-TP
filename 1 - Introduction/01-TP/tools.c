#include "tools.h"

void copyFile(char* src, char* dest){

    int srcFile = open(src, O_RDONLY);
    int destFile = open(dest,O_WRONLY | O_CREAT, 0666);

    if(srcFile == -1){
        printf("Error on the opening of the sourcefile : %s\n", strerror(errno));
        return;
    }
    if(destFile == -1){
        printf("Error on the opening of the destfile: %s\n", strerror(errno));
        return;
    }

    char c;

    while(read(srcFile, &c, 1) > 0){
        write(destFile, &c, 1);
    }

    if (close(srcFile) == -1) {
        printf("Error on the close of the source file: %s\n", strerror(errno));
    }

    if (close(destFile) == -1) {
        printf("Error on the close of the destination file: %s\n", strerror(errno));
    }

    printf("File copied successfuly\n");
}

void reverse(char* src){

    int srcFile = open(src, O_RDONLY);

    if(srcFile == -1){
        printf("Error: %s\n", strerror(errno));
        return;
    }

    int value = lseek(srcFile, 0, SEEK_END);

    if(value == -1){
        printf("Error: %s\n", strerror(errno));
        return;
    }

    char c;

    while(value >0){
        lseek(srcFile, value-1, SEEK_SET);

        if(read(srcFile, &c, 1) == -1){
            printf("Error: %s\n", strerror(errno));
            return;
        }

        printf("%c", c);
        value--;
    }

    if(close(srcFile)!=0){
        printf("Error: %s\n", strerror(errno));
    }

}

void ls(char* src) {
    DIR* srcFolder = opendir(src);

    if (srcFolder == NULL) {
        printf("Error sur l'ouverture du dossier source : %s\n", strerror(errno));
        return;
    }

    struct dirent* directory;
    struct stat fileStat;
    struct passwd* pwd;
    struct group* grp;
    struct tm* tm;

    while ((directory = readdir(srcFolder)) != NULL) {

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", src, directory->d_name);

        if (stat(fullPath, &fileStat) == -1) {
            printf("Erreur lors de l'obtention des informations sur %s : %s\n", directory->d_name, strerror(errno));
            continue;
        }

        printf("--------------------\n");
        printf("File Name: \t\t%s\n", directory->d_name);

        printf("File Permissions: \t");
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");

        pwd = getpwuid(fileStat.st_uid);
        if (pwd != NULL) {
            printf("User id: \t\t%s\n", pwd->pw_name);
        }

        grp = getgrgid(fileStat.st_gid);
        if (grp != NULL) {
            printf("Group id: \t\t%s\n", grp->gr_name);
        }

        printf("File Size: \t\t%lld bytes\n", (long long)fileStat.st_size);

        tm = localtime(&fileStat.st_mtime);
        if (tm != NULL) {
            printf("Last modification: \t%s", asctime(tm));
        }
    }

    if (closedir(srcFolder) == 0) {
        printf("srcFolder closed\n");
    } else {
        printf("Error: %s\n", strerror(errno));
    }
}
FICHIER my_open(const char *path, const char *mode) {
    FICHIER file;
    file.file = -1;
    file.index = 0;
    file.size = 0;

    if (strcmp(mode, "r") == 0) {
        file.file = open(path, O_RDONLY);
        if (file.file == -1) {
            printf("Error opening file in read mode: %s\n", strerror(errno));
            return file;
        }
        file.mode = 'r';
        file.size = read(file.file, file.buffer, sizeof(file.buffer));
        if (file.size == -1) {
            printf("Error reading file: %s\n", strerror(errno));
            close(file.file);
            file.file = -1;
        }
    } else if (strcmp(mode, "w") == 0) {
        file.file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file.file == -1) {
            printf("Error opening file in write mode: %s\n", strerror(errno));
            return file;
        }
        file.mode = 'w';
    } else {
        printf("Invalid mode: %s. Use 'r' or 'w'.\n", mode);
    }

    return file;
}

char my_getc(FICHIER *file) {
    if (file->index >= file->size) {
        file->size = read(file->file, file->buffer, sizeof(file->buffer));
        file->index = 0;

        if (file->size <= 0) {
            return EOF;
        }
    }

    return file->buffer[file->index++];
}

void my_putc(char c, FICHIER *file) {
    if (file->mode != 'w') {
        printf("File is not opened in write mode.\n");
        return;
    }

    file->buffer[file->index++] = c;

    if (file->index >= (int)sizeof(file->buffer)) {
        if (write(file->file, file->buffer, file->index) == -1) {
            printf("Error writing to file: %s\n", strerror(errno));
        }
        file->index = 0;
    }
}


void my_close(FICHIER *file) {
    if (file->mode == 'w' && file->index > 0) {
        if (write(file->file, file->buffer, file->index) == -1) {
            printf("Error writing remaining data: %s\n", strerror(errno));
        }
    }

    if (close(file->file) == -1) {
        printf("Error closing file: %s\n", strerror(errno));
    } else {
        printf("File closed successfully.\n");
    }

    file->file = -1;
}