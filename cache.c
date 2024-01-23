#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CODES 2000
#define MAX_LINE_LENGTH 1024
Cache geocaches[MAX_CODES];

// varivel para verificar se o arquivo foi carregado
int fileLoaded = 0;

// Função (FoundP) para comparar duas caches e verificar se são iguais.
int compareCaches(const Cache *cache1, const Cache *cache2) {
    return strcmp(cache1->code, cache2->code);
}
// Limpa as caches da memória.
void clearGeocaches(int *geocacheCount) {
    *geocacheCount = 0;
    printf("\nGeocaches cleared.\n");
}
 
void getGeocaches(const char file[], Cache geocaches[], int *geocacheCount) {
    

    // Abre o arquivo no modo de leitura
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("\nFile not found.\n");
        return;
    }
 
    // Variáveis para armazenar a linha lida, o delimitador e os tokens
    char line[MAX_LINE_LENGTH];
    const char delimiter[] = ";";
 
    // Lê e descarta a linha de cabeçalho
    fgets(line, sizeof(line), f);
 
    // Loop para ler as linhas do arquivo e carregar as geocaches
    while (fgets(line, sizeof(line), f) && *geocacheCount < MAX_CODES) {
        // Inicializa uma nova estrutura Cache
        Cache gc = {0};
 
        // Tokeniza a linha usando o delimitador ";"
        char *token = strtok(line, delimiter);
 
        // Atribui os tokens às variáveis da estrutura Cache
        if (token) gc.code = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.name = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.state = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.owner = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.latitude = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.longitude = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.kind = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.size = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.difficulty = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.terrain = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.status = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.hidden_date = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.founds = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.not_found = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.favourites = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.altitude = atoi(token);
 
        // Verifica se a geocache já existe no array antes de armazená-la
        int cacheExists = 0;
        for (int i = 0; i < *geocacheCount; i++) {
            if (compareCaches(&geocaches[i], &gc) == 0) {
                cacheExists = 1;
                break;
            }
        }
 
        // Se a geocache não existe, armazena-a no array
        if (!cacheExists) {
            geocaches[*geocacheCount] = gc;
            (*geocacheCount)++;
        }
    }
 
    // Fecha o arquivo após a leitura
    fclose(f);
 
    // Indica a quantidade de geocaches carregadas
    printf("\n%d unique geocaches loaded.\n", *geocacheCount);

    
}
// Mostra as geocaches que estão guardadas na memória (LOAD)
void printGeocacheDetails(const Cache cache, int index) {
    // Dá print no header, se for a primeira "geocache"
    if (index == 0) {
        printf("| %-7s | %-50s | %-22s | %-22s | %-9s | %-10s | %-11s | %-10s | %-9s | %-8s | %-9s | %-9s | %-6s | %-9s | %-10s | %-8s |\n",
            "Code", "Name", "State", "Owner", "Latitude", "Longitude", "Kind", "Size", "Difficulty", "Terrain", "Status", "Hidden Date", "Founds", "Not Founds", "Favourites", "Altitude");
    }
    // Print os detalhes do geocache
    printf("\n| %-7s | %-50s | %-22s | %-22s | %-9f | %-10f | %-11s | %-10s | %-10f | %-7f | %-9s | %-11s | %-6d | %-10d | %-10d | %-8d |",
        cache.code,
        cache.name,
        cache.state,
        cache.owner,
        cache.latitude,
        cache.longitude,
        cache.kind,
        cache.size,
        cache.difficulty,
        cache.terrain,
        cache.status,
        cache.hidden_date,
        cache.founds,
        cache.not_found,
        cache.favourites,
        cache.altitude);
}

void listGeocaches(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\nNo geocaches to display.\n");
        return;
    }

    printf("\nListing all geocaches:\n");

    // Imprime os detalhes de cada cache e a percentagem de aparecimento
    for (int i = 0; i < geocacheCount; i++) {
        printGeocacheDetails(geocaches[i], i);

        
    }
}

// Função para listar geocaches com percentagem de aparecimento
void foundPGeocaches(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\nNo geocaches to display.\n");
        return;
    }


    // Cria um array para contar as ocorrências de cada cache
    int occurrences[MAX_CODES] = {0};

    // Conta as ocorrências de cada cache
    for (int i = 0; i < geocacheCount; i++) {
        occurrences[i]++;
        for (int j = i + 1; j < geocacheCount; j++) {
            if (strcmp(geocaches[i].code, geocaches[j].code) == 0) {
                occurrences[i]++;
                occurrences[j]++;
            }
        }
    }

    // Imprime os detalhes de cada cache e a percentagem de aparecimento
    for (int i = 0; i < geocacheCount; i++) {
        printGeocacheDetails(geocaches[i], i);

        // Calcula a percentagem de aparecimento da cache
        float percentage = (float)geocaches[i].founds / (geocaches[i].not_found + geocaches[i].founds) * 100;
        printf("Percentage of appearance: %.2f%%\n", percentage);
    }
}
