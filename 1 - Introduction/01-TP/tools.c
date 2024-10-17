#include "tools.h"

int triple(int a){
    return a*3;
}

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
    }
    
}