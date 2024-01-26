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
    printf("\n1 - LOAD\n2 - CLEAR\n3 - LIST\n4 - FOUNDP\n0 - QUIT\n\nChoose an option: ");
}

int main() {
    // Variables
    Cache geocaches[MAX_CODES];
    int cachesLoaded = 0;
    int menuOption;
    char file[256];

    do {
        printMenu(); // Call the function to print the menu
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
            case 2: // CLEAR function
                clearCaches(&cachesLoaded);
                break;
            case 3: // LIST function
                listGeocaches(geocaches, cachesLoaded);
                break;
            case 4: // FOUNDP function
                foundPGeocaches(geocaches, cachesLoaded);
                break;
            case 0: // QUIT function
                printf("\nExit Success!\n");
                printf("\n");
                return EXIT_SUCCESS;
            default:
                printf("\nInvalid option. Please try again with a valid command.\n");
        }
        
    } while (menuOption != 0); // The menu is displayed until the QUIT option (0) is selected.
    
    return EXIT_SUCCESS;
}
