#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "input.h"
#include <ctype.h>

void printMenu() {
    printf("\n******************************");
    printf("\n********* GEOCACHING *********\n");
    printf("******************************\n");
    printf("\n1 - LOAD\n2 - CLEAR\n3 - LIST\n4 - FOUNDP\n5 - SEARCH\n6 - EDIT\n7 - CENTER\n8 - STATEC\n9 - SAVE\n10 - M81\n11 - SORT\n0 - QUIT\n\nChoose an option: ");
}

int main() {
    // Variables
    Cache geocaches[MAX_CODES];
    int cachesLoaded = 0;
    int menuOption;
    char file[256];

    do {
        printMenu(); // Função para apresentar o menu
        scanf("%d", &menuOption);
        getchar();

        switch(menuOption) {
            case 1: // LOAD function
                if (cachesLoaded > 0) {
                    printf("\nCache data exists. Please clear it first.\n");
                 } else {
                    printf("\nEnter filename: ");
                    scanf("%255s", file);
                    getGeocaches(file, geocaches, &cachesLoaded);
                 } 
                break;
            case 2: // Função CLEAR - limpa as geocaches carregadas na memória.
                clearCaches(&cachesLoaded);
                break;
            case 3: // Função list - mostra a lista de geocaches em tabela
                listGeocaches(geocaches, cachesLoaded);
                break;
            case 4: // Função FoundP - mostra a percentagem de aparecimento das caches.
                foundPGeocaches(geocaches, cachesLoaded);
                break;
            case 5:
            //Função SEARCH - procura uma geocache pelo código
                searchGeocache(geocaches, cachesLoaded);
                break;
            case 6:
            // Função EDIT - edita informações de uma geocache
                editGeocache(geocaches, cachesLoaded);
                break;
            case 7:
            // Função CENTER - calcula média e desvio padrão das latitudes e longitudes
                center(geocaches, cachesLoaded);
                break;
            case 8:
                // FUNÇÃO STATEC
                STATEC(geocaches,cachesLoaded);
                break;
            case 9:
                SAVE(geocaches, cachesLoaded);
                break;
            case 10:
                M81(geocaches, cachesLoaded);
                break;
            case 11:
                SORT(geocaches, cachesLoaded);
                break;
            case 0: // Função quit
                printf("\nExit Success!\n");
                printf("\n");
                return EXIT_SUCCESS;
            default:
                printf("\nInvalid option. Please try again with a valid command.\n");
        }
        
    } while (menuOption != 0); // O menu é mostrado até que o utilizador selecione a opção 0 = exit.
    
    return EXIT_SUCCESS;
}
