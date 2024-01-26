#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"



int main() {
    // Variaveis 
    Cache geocaches[MAX_CODES];
    int cachesLoaded = 0;
    int menuOption;
    char file[256];


    do {
        // Menu Geocache
        printf("\n******************************");
        printf("\n********* GEOCACHING *********\n");
        printf("******************************\n");
        printf("\n1 - LOAD\n2 - CLEAR\n3 - LIST\n4 - FOUNDP\n0 - QUIT\n\nChoose an option: ");
        scanf("%d", &menuOption);
        getchar(); // Limpa o buffer do teclado

        switch(menuOption) {
            case 1: //Função LOAD - lê o ficheiro e guarda os dados na memória.

                if (cachesLoaded > 0) {
                printf("\nCache data exists. Please clear it first.\n");
                 } else {
                printf("\nEnter filename: ");
                scanf("%255s", file);
                getGeocaches(file, geocaches, &cachesLoaded);
                 } 
                break;
            case 2://Função CLEAR - limpa os dados da memória.
                clearGeocaches(&cachesLoaded);
                // fileLoaded = 0;
                break;
            case 3://Função LIST - mostra os dados que estão carregados na memória.
                listGeocaches(geocaches, cachesLoaded);
                break;
            case 4://Função FOUNP - mostra a percentagem de aparecimento da cache.
                foundPGeocaches(geocaches, cachesLoaded);
                break;
            case 0://Função QUIT - Termina o programa.
                printf("\nExit Success!\n");
                printf("\n");
                return EXIT_SUCCESS;
                break;
            default:
                printf("\nInvalid option.\n");
        }
    } while (menuOption != 0); // O menu é apresentando até ser selecionada a opção 0 - Quit.

    
    return EXIT_SUCCESS;
}
