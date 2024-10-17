#include "tools.h"

int main(int argc, char** argv) {


    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    if (argc < 2) {
        printf("USAGE : ./TP1 [option] [src] [dest]\n");
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        if (argc >= 4) {
            copyFile(argv[2], argv[3]);
        } else {
            printf("USAGE : ./TP1 1 [srcFile] [destFile]\n");
        }
    }
    else if (strcmp(argv[1], "2") == 0) {
        if (argc >= 3) {
            reverse(argv[2]);
        } else {
            printf("USAGE : ./TP1 2 [srcFile]\n");
        }
    }
    else if (strcmp(argv[1], "3") == 0) {
        if (argc >= 3) {
            ls(argv[2]);
        } else {
            printf("USAGE : ./TP1 3 [srcFolder]\n");
        }
    }    
    else if (strcmp(argv[1], "4") == 0) {
        if (argc >= 3) {
            /* Exo 4*/
        } else {
            printf("USAGE : ./TP1 4\n");
        }
    
    }
    else {
        printf("Option inconnue : %s\n", argv[1]);
        printf("USAGE : ./TP1 [1|2|3] [src|number] [dest]\n");
    }

    return 0;
}