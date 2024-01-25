#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    printf("\n\033[1;33mGeocaches cleared.\n\033[0m");
}
 
void getGeocaches(const char file[], Cache geocaches[], int *geocacheCount) {
    

    // Abre o arquivo no modo de leitura
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("\n\033[1;31mFile not found.\n\033[0m");
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
    printf("\n\033[1;33m%d unique geocaches loaded.\n\033[0m", *geocacheCount);

    
}
// Mostra as geocaches que estão guardadas na memória (LOAD)
void printGeocacheDetails(const Cache cache, int index) {
    printf("\n\033[1;33mCache %d:\033[0m \n Code: %s, Name: %s, State: %s, Owner: %s, Latitude: %.6f, Longitude: %.6f, Kind: %s, Size: %s, Difficulty: %.1f, Terrain: %.1f, Status: %s, Hidden date: %s, Founds: %d, Not founds: %d, Favourites: %d, Altitude: %d\n",
        index + 1,
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
        printf("\n\033[1;33mNo geocaches to display.\n\033[0m");
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
    float percentage;

    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;31mNo geocaches loaded.\n\033[0m");
        return;
    }

    for (int i = 0; i < geocacheCount; i++) {
        percentage = (float)geocaches[i].founds / (geocaches[i].not_found + geocaches[i].founds) * 100;;

        printf("\n\033[1;33mCache %d:\033[0m \n Percentage: %.2f%%\n Code: %s, Name: %s, State: %s, Owner: %s, Latitude: %.6f, Longitude: %.6f, Kind: %s, Size: %s, Difficulty: %.1f, Terrain: %.1f, Status: %s, Hidden date: %s, Founds: %d, Not founds: %d, Favourites: %d, Altitude: %d\n",
        i + 1,
        percentage,
        geocaches[i].code,
        geocaches[i].name,
        geocaches[i].state,
        geocaches[i].owner,
        geocaches[i].latitude,
        geocaches[i].longitude,
        geocaches[i].kind,
        geocaches[i].size,
        geocaches[i].difficulty,
        geocaches[i].terrain,
        geocaches[i].status,
        geocaches[i].hidden_date,
        geocaches[i].founds,
        geocaches[i].not_found,
        geocaches[i].favourites,
        geocaches[i].altitude);
    }
}

// Função para procurar uma geocache pelo código
void searchGeocache(const Cache geocaches[], int geocacheCount) {
    char searchCode[255];
    printf("\n\033[1;33mEnter cache code to search: \033[0m");
    scanf("%255s", searchCode);
    getchar(); // Limpa o buffer do teclado

    // Procura pela geocache com o código fornecido
    int cacheIndex = -1;
    for (int i = 0; i < geocacheCount; i++) {
        if (strcmp(geocaches[i].code, searchCode) == 0) {
            cacheIndex = i;
            break;
        }
    }

    // Exibe os detalhes da geocache se encontrada, caso contrário, exibe a mensagem de não encontrada
    if (cacheIndex != -1) {
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);
    } else {
        printf("\n\033[1;33m<Cache not found>\n\033[0m");
    }
}

// Função para editar informações de uma geocache
void editGeocache(Cache *geocaches, int geocacheCount) {
    char searchCode[255];  // Alterado para 6 para incluir o caractere nulo '\0'
    printf("\n\033[1;33mEnter cache code to edit: \033[0m");
    scanf("%255s", searchCode);
    getchar(); // Limpa o buffer do teclado

    // Procura pela geocache com os primeiros 5 caracteres do código fornecido
    int cacheIndex = -1;
    for (int i = 0; i < geocacheCount; i++) {
        if (strcmp(geocaches[i].code, searchCode) == 0) {
            cacheIndex = i;
            break;
        }
    }

    // Exibe os detalhes da geocache se encontrada, caso contrário, exibe a mensagem de não encontrada
    if (cacheIndex != -1) {
        // Apresenta os detalhes da geocache antes da edição
        printf("\n\033[1;33mCache details before edit:\033[0m");
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);

        // Opções de edição
        printf("\n\033[1;37mSelect information to edit:\033[0m");
        printf("\n1 - Owner\n2 - Status\n3 - Hidden Date\n4 - Altitude\n0 - Cancel\n");

        int editOption;
        printf("\n\033[1;32mChoose an option: \033[0m");
        scanf("%d", &editOption);
        getchar(); // Limpa o buffer do teclado

        switch (editOption) {
            case 1:
                printf("\n\033[1;33mEnter new owner: \033[0m");
                scanf("%255s", geocaches[cacheIndex].owner);
                break;
            case 2:
                printf("\n\033[1;33mEnter new status: \033[0m");
                scanf("%255s", geocaches[cacheIndex].status);
                break;
            case 3:
                printf("\n\033[1;33mEnter new hidden date: \033[0m");
                scanf("%255s", geocaches[cacheIndex].hidden_date);
                break;
            case 4:
                printf("\n\033[1;33mEnter new altitude: \033[0m");
                scanf("%d", &geocaches[cacheIndex].altitude);
                break;
            case 0:
                printf("\n\033[1;33mEdit canceled.\n\033[0m");
                break;
            default:
                printf("\n\033[1;33mInvalid option.\n\033[0m");
                break;
        }

        // Apresenta os detalhes da geocache após a edição
        printf("\n\033[1;33mCache details after edit:\033[0m");
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);
    } else {
        printf("\n\033[1;33m<Cache not found>\n\033[0m");
    }
}

// Função para calcular a média e o desvio padrão das latitudes e longitudes
void center(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches to calculate statistics.\n\033[0m");
        return;
    }

    double sumLatitudes = 0.0;
    double sumLongitudes = 0.0;

    // Calcular a soma das latitudes e longitudes
    for (int i = 0; i < geocacheCount; i++) {
        sumLatitudes += geocaches[i].latitude;
        sumLongitudes += geocaches[i].longitude;
    }

    // Calcular a média das latitudes e longitudes
    double meanLatitude = sumLatitudes / geocacheCount;
    double meanLongitude = sumLongitudes / geocacheCount;

    double sumLatSquared = 0.0;
    double sumLongSquared = 0.0;

    // Calcular a soma dos quadrados das diferenças para o cálculo da variância
    for (int i = 0; i < geocacheCount; i++) {
        sumLatSquared += pow(geocaches[i].latitude - meanLatitude, 2);
        sumLongSquared += pow(geocaches[i].longitude - meanLongitude, 2);
    }

    // Calcular o desvio padrão das latitudes e longitudes
    double stddevLatitude = sqrt(sumLatSquared / geocacheCount);
    double stddevLongitude = sqrt(sumLongSquared / geocacheCount);

    // Exibir as estatísticas
    printf("\n\033[1;33mStatistics for Geocaches:\n\033[0m");
    printf("Average Latitude: %.6f, Standard Deviation Latitude: %.6f\n", meanLatitude, stddevLatitude);
    printf("Average Longitude: %.6f, Standard Deviation Longitude: %.6f\n", meanLongitude, stddevLongitude);
}

// Função para mostrar a contagem de caches para cada distrito e status
void STATEC(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches loaded.\n\033[0m");
        return;
    }

    // Definir estrutura para armazenar contagens por distrito e status
    typedef struct {
        char state[255];
        int availableCount;
        int inactiveCount;
    } StateCount;

    // Inicializar array para armazenar contagens
    StateCount stateCounts[MAX_CODES];
    int stateCount = 0;

    // Inicializar contagens para cada distrito
    for (int i = 0; i < geocacheCount; i++) {
        int stateIndex = -1;

        // Verificar se o distrito já está na lista de contagens (ignorar maiúsculas e minúsculas)
        for (int j = 0; j < stateCount; j++) {
            if (strcasecmp(stateCounts[j].state, geocaches[i].state) == 0) {
                stateIndex = j;
                break;
            }
        }

        // Se o distrito não está na lista, adicioná-lo
        if (stateIndex == -1) {
            strcpy(stateCounts[stateCount].state, geocaches[i].state);
            stateCounts[stateCount].availableCount = 0;
            stateCounts[stateCount].inactiveCount = 0;
            stateIndex = stateCount;
            stateCount++;
        }

        // Incrementar contagem com base no status da cache (ignorar maiúsculas e minúsculas)
        if (strcasecmp(geocaches[i].status, "Available") == 0) {
            stateCounts[stateIndex].availableCount++;
        } else if (strcasecmp(geocaches[i].status, "Inactive") == 0) {
            stateCounts[stateIndex].inactiveCount++;
        }
    }

    // Exibir contagens por distrito e status
    printf("\n\033[1;33mCache Counts by State and Status:\n\033[0m");
    for (int i = 0; i < stateCount; i++) {
        printf("\n\033[1;33mState: %s\n\033[0m", stateCounts[i].state);
        printf("Available: %d caches\n", stateCounts[i].availableCount);
        printf("Inactive: %d caches\n", stateCounts[i].inactiveCount);
    }
}

// Função para salvar as informações de caches em um arquivo CSV
void SAVE(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches loaded.\n\033[0m");
        return;
    }

    char fileName[256];

    // Solicitar ao usuário o nome do arquivo
    printf("\n\033[1;33mEnter the file name to save (including .csv extension): \033[0m");
    scanf("%255s", fileName);

    // Verificar se o arquivo já existe
    FILE *checkFile = fopen(fileName, "r");
    if (checkFile != NULL) {
        fclose(checkFile);
        printf("\n\033[1;31mFile with the same name already exists. Save aborted.\n\033[0m");
        return;
    }

    // Abrir o arquivo para escrita
    FILE *file = fopen(fileName, "w");
    if (!file) {
        printf("\n\033[1;31mError opening file for writing.\n\033[0m");
        return;
    }

    // Escrever cabeçalho no arquivo CSV
    fprintf(file, "Code,Name,State,Owner,Latitude,Longitude,Kind,Size,Difficulty,Terrain,Status,HiddenDate,Founds,NotFounds,Favourites,Altitude\n");

    // Escrever informações de cada geocache no arquivo CSV
    for (int i = 0; i < geocacheCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%.6f,%.6f,%s,%s,%.1f,%.1f,%s,%s,%d,%d,%d,%d\n",
                geocaches[i].code,
                geocaches[i].name,
                geocaches[i].state,
                geocaches[i].owner,
                geocaches[i].latitude,
                geocaches[i].longitude,
                geocaches[i].kind,
                geocaches[i].size,
                geocaches[i].difficulty,
                geocaches[i].terrain,
                geocaches[i].status,
                geocaches[i].hidden_date,
                geocaches[i].founds,
                geocaches[i].not_found,
                geocaches[i].favourites,
                geocaches[i].altitude);
    }

    // Fechar o arquivo
    fclose(file);

    printf("\n\033[1;32mData saved successfully.\n\033[0m");
}

// Função para calcular a matriz 81
void M81(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches loaded.\n\033[0m");
        return;
    }

    // Definir uma estrutura para armazenar contagens por terreno/dificuldade
    typedef struct {
        double difficulty;
        double terrain;
        int count;
    } DifficultyTerrainCount;

    // Inicializar uma matriz 9x9 para armazenar contagens
    DifficultyTerrainCount matrix81[9][9];

    // Inicializar a matriz com contagens zeradas
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            matrix81[i][j].difficulty = i + 1;  // Dificuldade varia de 1 a 9
            matrix81[i][j].terrain = j + 1;    // Terreno varia de 1 a 9
            matrix81[i][j].count = 0;
        }
    }

    // Preencher a matriz com contagens reais
    for (int i = 0; i < geocacheCount; i++) {
        int difficultyIndex = (int)geocaches[i].difficulty - 1;
        int terrainIndex = (int)geocaches[i].terrain - 1;

        // Incrementar a contagem para a combinação de terreno/dificuldade correspondente
        matrix81[difficultyIndex][terrainIndex].count++;
    }

    // Exibir a matriz 81
    printf("\n\033[1;33mMatrix 81 (Difficulty x Terrain):\n\033[0m");
    printf("\n\033[1;33m    Terrain\\Difficulty 1   2   3   4   5   6   7   8   9\n\033[0m");
    printf("\033[1;33m--------------------------------------------------------\n\033[0m");

    for (int i = 0; i < 9; i++) {
        printf("\033[1;33m%12.1f |", matrix81[i][0].difficulty);

        for (int j = 0; j < 9; j++) {
            printf(" %2d ", matrix81[i][j].count);
        }

        printf("\n");
    }
}

// Função para comparar caches por altitude (decrescente)
int compareByAltitude(const void *a, const void *b) {
    return ((Cache *)b)->altitude - ((Cache *)a)->altitude;
}

// Função para comparar caches por state (de A-Z, desempate por founds decrescente)
int compareByState(const void *a, const void *b) {
    int stateCompare = strcmp(((Cache *)a)->state, ((Cache *)b)->state);
    if (stateCompare != 0) {
        return stateCompare;
    }
    // Em caso de empate no estado, desempate por founds decrescente
    return ((Cache *)b)->founds - ((Cache *)a)->founds;
}

// Função para comparar caches por hidden_date (mais recente para mais antiga)
int compareByHiddenDate(const void *a, const void *b) {
    return strcmp(((Cache *)b)->hidden_date, ((Cache *)a)->hidden_date);
}

// Função para ordenar e mostrar a listagem de caches
void SORT(Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches loaded.\n\033[0m");
        return;
    }

    int sortOption;

    // Solicitar ao usuário a forma de ordenação
    printf("\n\033[1;33mChoose sorting option:\n");
    printf("1 - By altitude (descending)\n");
    printf("2 - By state (A-Z, tiebreaker by founds descending)\n");
    printf("3 - By hidden_date (most recent to oldest)\n");
    printf("Enter your choice (1-3): \033[0m");
    scanf("%d", &sortOption);

    // Realizar a ordenação com base na escolha do usuário
    switch (sortOption) {
        case 1:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByAltitude);
            break;
        case 2:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByState);
            break;
        case 3:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByHiddenDate);
            break;
        default:
            printf("\n\033[1;33mInvalid sorting option.\n\033[0m");
            return;
    }

    // Exibir a listagem ordenada
    printf("\n\033[1;33mSorted Geocache Listing:\n\033[0m");
    for (int i = 0; i < geocacheCount; i++) {
        printGeocacheDetails(geocaches[i], i);
    }
}
