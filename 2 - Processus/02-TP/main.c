#include "tools.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("USAGE : ./TP2 [option]\n");
        printf("Erreur : %s\n", strerror(EINVAL));


    }

    if (strcmp(argv[1], "1") == 0) {
        if (argc >= 2) {
            forkYourself();
        } else {
            printf("USAGE : ./TP2 1  \n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }

    if (strcmp(argv[1], "2") == 0) {
        if (argc >= 3) {
            redirectionStandard(argv[2]);
        } else {
            printf("USAGE : ./TP2 2 [Command] \n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }

    if(strcmp(argv[1], "3") == 0){
        if (argc >= 2) {
            redirectionPipe();
        } else {
            printf("USAGE : ./TP2 3 \n");
            printf("Erreur : %s\n", strerror(EINVAL));
        }
    }

   
    else {
        printf("Option inconnue : %s\n", argv[1]);
        printf("USAGE : ./TP2 [1|2|3]\n");
        printf("Erreur : %s\n", strerror(EINVAL));
    }
    return 0;
}