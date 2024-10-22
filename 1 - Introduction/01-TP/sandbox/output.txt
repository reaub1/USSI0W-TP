#include "tools.h"

void copyFile(char* src, char* dest){

    int srcFile = open(src, O_RDONLY);
    int destFile = open(dest,O_WRONLY | O_CREAT, 0666);

    char c;

    while(read(srcFile, &c, 1) > 0){
        write(destFile, &c, 1);
    }

    close(srcFile);
    close(destFile);
}

void reverse(char* src){

    int srcFile = open(src, O_RDONLY);

    int value = lseek(srcFile, 0, SEEK_END);

    char c;

    while(value >0){
        lseek(srcFile, value-1, SEEK_SET);
        read(srcFile, &c, 1);
        printf("%c", c);
        value--;
    }

    close(srcFile);
}

void ls(char* src){
    DIR* srcFolder = opendir(src);

    struct dirent* directory = readdir(srcFolder);

    struct stat fileStat;
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;

    while(directory != NULL){
        printf("%s\n", directory->d_name);

        stat(directory->d_name, &fileStat);

        printf("--------------------\n");

        printf("File Name: \t\t%s\n", directory->d_name);

        printf("File Permissions: \t");

        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");

        pwd = getpwuid(fileStat.st_uid);
        printf("User id: \t\t%s\n", pwd->pw_name);

        grp = getgrgid(fileStat.st_gid);
        printf("Group id: \t\t%s\n", grp->gr_name);

        printf("File Size: \t\t%lld bytes\n", fileStat.st_size);

        tm = localtime(&fileStat.st_mtime);

        printf("Last modification: \t%s", asctime(tm));

        directory = readdir(srcFolder);
 
        closedir(srcFolder);
    }
}

FICHIER my_open(const char *path, const char *mode){

    FICHIER file;

    if(strcmp(mode, "r") == 0){
        file.file = open(path, O_RDONLY);
    }else if(strcmp(mode, "w") == 0){
        file.file = open(path, O_WRONLY | O_CREAT, 0666);
    }

    char c; 

    file.index = 0;

    while(read(file.file, &c, 1) > 0){
        file.buffer[file.index] = c;
        file.index++;
    }

    return file;
}

char my_getc(FICHIER file){
    if(file.index > 0){
        file.index--;
        return file.buffer[file.index];
    }else{
        return EOF;
    }
}

char my_putc(char c, FICHIER file){
    file.buffer[file.index] = c;
    file.index++;
    return c;
}

void my_close(FICHIER file){
    close(file.file);
}