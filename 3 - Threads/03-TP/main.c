#include "tools.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("USAGE : ./TP3 [option]\n");
        printf("Erreur : %s\n", strerror(EINVAL));


    }

    if (strcmp(argv[1], "1") == 0) {
        if (argc >= 2) {
            //TO DO
        } else {
            printf("USAGE : ./TP3 1  \n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }

   
    else {
        printf("Option inconnue : %s\n", argv[1]);
        printf("USAGE : ./TP3 [1|2|3]\n");
        printf("Erreur : %s\n", strerror(EINVAL));
    }
    return 0;
}