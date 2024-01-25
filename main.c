#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"



int main() {
    // Variaveis 
    Cache geocaches[MAX_CODES];
    int geocacheCount = 0;
    int menuOption;
    char file[256];
    int fileLoaded = 0;


    do {
        // Menu Geocache
        printf("\033[1;32m\n******************************\033[0m");
        printf("\033[1;32m\n********* GEOCACHING *********\033[0m\n");
        printf("\033[1;32m******************************\033[0m\n");
        printf("\033[1;37m\n1 - LOAD\n2 - CLEAR\n3 - LIST\n4 - FOUNDP\n5 - SEARCH\n6 - EDIT\n7 - CENTER\n8 - STATEC\n9 - SAVE\n10 - M81\n11 - SORT\n12 - AGE\n0 - QUIT\n\n\033[0m\033[1;32mChoose an option: \033[0m");
        scanf("%d", &menuOption);
        getchar(); // Limpa o buffer do teclado

        switch(menuOption) {
            case 1:
            //Função LOAD - lê o ficheiro e guarda os dados na memória.
                if (fileLoaded > 0) {
                printf("\n\033[1;33mCache data exists. Please clear it first.\n\033[0m");
                 } else {
                fileLoaded += 1;
                printf("\n\033[1;33mEnter filename: \033[0m");
                scanf("%255s", file);
                getGeocaches(file, geocaches, &geocacheCount);
                 } 
                break;
            case 2:
            //Função CLEAR - limpa os dados da memória.
                clearGeocaches(&geocacheCount);
                fileLoaded = 0;
                break;
            case 3:
            //Função LIST - mostra os dados que estão carregados na memória.
                listGeocaches(geocaches, geocacheCount);
                break;
            case 4:
            //Função FOUNP - mostra a percentagem de aparecimento da cache.
                foundPGeocaches(geocaches, geocacheCount);
                break;
            case 5:
            //Função SEARCH - procura uma geocache pelo código
                searchGeocache(geocaches, geocacheCount);
                break;
            case 6:
            // Função EDIT - edita informações de uma geocache
                editGeocache(geocaches, geocacheCount);
                break;
            case 7:
            // Função CENTER - calcula média e desvio padrão das latitudes e longitudes
                center(geocaches, geocacheCount);
                break;
            case 8:
                // Chamar a função AGE
                STATEC(geocaches,geocacheCount);
                break;
            case 9:
                SAVE(geocaches, geocacheCount);
                break;
            case 10:
                M81(geocaches, geocacheCount);
                break;
            case 11:
                SORT(geocaches, geocacheCount);
                break;
            case 0:
            //Função QUIT - Termina o programa.
                printf("\n\033[1;31mExit Success!\033[0m\n");
                printf("\n");
                return EXIT_SUCCESS;
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (menuOption != 0); // O menu é apresentando até ser selecionada a opção 0 - Quit.

    
    return EXIT_SUCCESS;
}
