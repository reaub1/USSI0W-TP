#include "tools.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("USAGE : ./TP1 [option]\n");
        printf("Erreur : %s\n", strerror(EINVAL));
    }

    if (strcmp(argv[1], "1") == 0) {
        if (argc >= 4) {
            copyFile(argv[2], argv[3]);
        } else {
            printf("USAGE : ./TP1 1 [srcFile] [destFile]\n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }
    else if (strcmp(argv[1], "2") == 0) {
        if (argc >= 3) {
            reverse(argv[2]);
        } else {
            printf("USAGE : ./TP1 2 [srcFile]\n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }
    else if (strcmp(argv[1], "3") == 0) {
        if (argc >= 3) {
            ls(argv[2]);
        } else {
            printf("USAGE : ./TP1 3 [srcFolder]\n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }    
    else if (strcmp(argv[1], "4") == 0) {
        if (argc >= 3) {
            FICHIER input = my_open(argv[2], "r");
            FICHIER output = my_open(argv[3], "w"); 

            char c;

            while((c = my_getc(input)) != EOF){
                my_putc(c, output);
            }

            my_close(input);
            my_close(output);

            printf("File copied\n");
        
        } else {
            printf("USAGE : ./TP1 4 [src] [dest]\n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    
    }
    else {
        printf("Option inconnue : %s\n", argv[1]);
        printf("USAGE : ./TP1 [1|2|3] [src|number] [dest]\n");
        printf("Erreur : %s\n", strerror(EINVAL));
    }
    return 0;
}