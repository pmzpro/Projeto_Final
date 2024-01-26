#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_CODES 2000
#define MAX_LINE_LENGTH 1024
Cache geocaches[MAX_CODES];

// Função (FoundP) para comparar duas caches e verificar se são iguais.
int compareCaches(const Cache *cache1, const Cache *cache2) {
    return strcmp(cache1->code, cache2->code);
}
// Limpa as caches da memória.
void clearCaches(int *cachesLoaded) {
    int verifyCache = *cachesLoaded;

    if(verifyCache >= 1){ // Se existir cache vai limpar.
    *cachesLoaded = 0;
    printf("\nGeocaches cleared.\n");
    } else if (verifyCache == 0){ // Se não existir cache vai informar que não existe nada para limpar
        printf("\nNo geocaches to clear.\n");
    }
   
}
 
void getGeocaches(const char file[], Cache geocaches[], int *cachesLoaded) {
    
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
    while (fgets(line, sizeof(line), f) && *cachesLoaded < MAX_CODES) {
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
        for (int i = 0; i < *cachesLoaded; i++) {
            if (compareCaches(&geocaches[i], &gc) == 0) {
                cacheExists = 1;
                break;
            }
        }
 
        // Se a geocache não existe, armazena-a no array
        if (!cacheExists) {
            geocaches[*cachesLoaded] = gc;
            (*cachesLoaded)++;
        }
    }
 
    // Fecha o arquivo após a leitura
    fclose(f);
 
    // Indica a quantidade de geocaches carregadas
    printf("\n%d unique geocaches loaded.\n", *cachesLoaded);

    
}

// Mostra as geocaches que estão guardadas na memória (LOAD)
void printGeocacheDetails(const Cache cache, int index) {
    // Dá print no header, se for a primeira "geocache"
    if (index == 0) {
        printf("| %-7s | %-50s | %-22s | %-22s | %-9s | %-10s | %-11s | %-10s | %-9s | %-8s | %-9s | %-9s | %-6s | %-9s | %-10s | %-8s |\n",
            "Code", "Name", "State", "Owner", "Latitude", "Longitude", "Kind", "Size", "Difficulty", "Terrain", "Status", "Hidden Date", "Founds", "Not Founds", "Favourites", "Altitude");
    }
    // Printa os detalhes do geocache
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

void listGeocaches(const Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches to display.\n");
        return;
    }

    printf("\nListing all geocaches:\n");

    // Imprime os detalhes de cada cache e a percentagem de aparecimento
    for (int i = 0; i < cachesLoaded; i++) {
        printGeocacheDetails(geocaches[i], i);
    }
}

// Função para listar geocaches com percentagem de aparecimento
void foundPGeocaches(const Cache geocaches[], int cachesLoaded) {
    float percentage;

    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches loaded.\n");
        return;
    }

    for (int i = 0; i < cachesLoaded; i++) {
        percentage = (float)geocaches[i].founds / (geocaches[i].not_found + geocaches[i].founds) * 100;;

        printf("\nCache %d: \n Percentage: %.2f%%\n Code: %s, Name: %s, State: %s, Owner: %s, Latitude: %.6f, Longitude: %.6f, Kind: %s, Size: %s, Difficulty: %.1f, Terrain: %.1f, Status: %s, Hidden date: %s, Founds: %d, Not founds: %d, Favourites: %d, Altitude: %d\n",
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

// FUNÇÕES DA SEGUNDA FASE COMEÇAM AQUI

// Função para procurar uma geocache pelo código
void searchGeocache(const Cache geocaches[], int cachesLoaded) {
    char searchCode[255];
    printf("\nEnter cache code to search: ");
    scanf("%255s", searchCode);
    getchar(); // Limpa o buffer do teclado

    // Procura pela geocache com o código fornecido
    int cacheIndex = -1;
    for (int i = 0; i < cachesLoaded; i++) {
        if (strcmp(geocaches[i].code, searchCode) == 0) {
            cacheIndex = i;
            break;
        }
    }

    // Exibe os detalhes da geocache se encontrada, caso contrário, exibe a mensagem de não encontrada
    if (cacheIndex != -1) {
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);
    } else {
        printf("\n<Cache not found>\n");
    }
}

// Função para editar informações de uma geocache
void editGeocache(Cache *geocaches, int cachesLoaded) {
    char searchCode[255];  // Alterado para 6 para incluir o caractere nulo '\0'
    printf("\nEnter cache code to edit: ");
    scanf("%255s", searchCode);
    getchar(); // Limpa o buffer do teclado

    // Procura pela geocache com os primeiros 5 caracteres do código fornecido
    int cacheIndex = -1;
    for (int i = 0; i < cachesLoaded; i++) {
        if (strcmp(geocaches[i].code, searchCode) == 0) {
            cacheIndex = i;
            break;
        }
    }

    // Exibe os detalhes da geocache se encontrada, caso contrário, exibe a mensagem de não encontrada
    if (cacheIndex != -1) {
        // Apresenta os detalhes da geocache antes da edição
        printf("\n\033Cache details before edit:");
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);

        // Opções de edição
        printf("\nSelect information to edit:");
        printf("\n1 - Owner\n2 - Status\n3 - Hidden Date\n4 - Altitude\n0 - Cancel\n");

        int editOption;
        printf("\nChoose an option: ");
        scanf("%d", &editOption);
        getchar(); // Limpa o buffer do teclado

        switch (editOption) {
            case 1:
                printf("\nEnter new owner: ");
                scanf("%255s", geocaches[cacheIndex].owner);
                break;
            case 2:
                printf("\nEnter new status: ");
                scanf("%255s", geocaches[cacheIndex].status);
                break;
            case 3:
                printf("\nEnter new hidden date: ");
                scanf("%255s", geocaches[cacheIndex].hidden_date);
                break;
            case 4:
                printf("\nEnter new altitude: ");
                scanf("%d", &geocaches[cacheIndex].altitude);
                break;
            case 0:
                printf("\nEdit canceled.\n");
                break;
            default:
                printf("\nInvalid option.\n");
                break;
        }

        // Apresenta os detalhes da geocache após a edição
        printf("\nCache details after edit:");
        printGeocacheDetails(geocaches[cacheIndex], cacheIndex);
    } else {
        printf("\n<Cache not found>\n");
    }
}

// Função para calcular a média e o desvio padrão das latitudes e longitudes
void center(const Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches to calculate statistics.\n");
        return;
    }

    double sumLatitudes = 0.0;
    double sumLongitudes = 0.0;

    // Calcular a soma das latitudes e longitudes
    for (int i = 0; i < cachesLoaded; i++) {
        sumLatitudes += geocaches[i].latitude;
        sumLongitudes += geocaches[i].longitude;
    }

    // Calcular a média das latitudes e longitudes
    double meanLatitude = sumLatitudes / cachesLoaded;
    double meanLongitude = sumLongitudes / cachesLoaded;

    double sumLatSquared = 0.0;
    double sumLongSquared = 0.0;

    // Calcular a soma dos quadrados das diferenças para o cálculo da variância
    for (int i = 0; i < cachesLoaded; i++) {
        sumLatSquared += pow(geocaches[i].latitude - meanLatitude, 2);
        sumLongSquared += pow(geocaches[i].longitude - meanLongitude, 2);
    }

    // Calcular o desvio padrão das latitudes e longitudes
    double stddevLatitude = sqrt(sumLatSquared / cachesLoaded);
    double stddevLongitude = sqrt(sumLongSquared / cachesLoaded);

    // Exibir as estatísticas
    printf("\nStatistics for Geocaches:\n");
    printf("Average Latitude: %.6f, Standard Deviation Latitude: %.6f\n", meanLatitude, stddevLatitude);
    printf("Average Longitude: %.6f, Standard Deviation Longitude: %.6f\n", meanLongitude, stddevLongitude);
}

// Função para mostrar a contagem de caches para cada distrito e status
void STATEC(const Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches loaded.\n");
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
    for (int i = 0; i < cachesLoaded; i++) {
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
        if (strcasecmp(geocaches[i].status, "AVAILABLE") == 0) {
            stateCounts[stateIndex].availableCount++;
        } else if (strcasecmp(geocaches[i].status, "DISABLED") == 0) {
            stateCounts[stateIndex].inactiveCount++;
        }
    }

    // Exibir contagens por distrito e status
    printf("\nCache Counts by State and Status:\n");
    for (int i = 0; i < stateCount; i++) {
        printf("\nState: %s\n", stateCounts[i].state);
        printf("Available: %d caches\n", stateCounts[i].availableCount);
        printf("Inactive: %d caches\n", stateCounts[i].inactiveCount);
    }
}

// Função para salvar as informações de caches em um arquivo CSV
void SAVE(const Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches loaded.\n");
        return;
    }

    char fileName[256];

    // Solicitar ao usuário o nome do arquivo
    printf("\nEnter the file name to save (including .csv extension): ");
    scanf("%255s", fileName);

    // Verificar se o arquivo já existe
    FILE *checkFile = fopen(fileName, "r");
    if (checkFile != NULL) {
        fclose(checkFile);
        printf("\nFile with the same name already exists. Save aborted.\n");
        return;
    }

    // Abrir o arquivo para escrita
    FILE *file = fopen(fileName, "w");
    if (!file) {
        printf("\nError opening file for writing.\n");
        return;
    }

    // Escrever cabeçalho no arquivo CSV
    fprintf(file, "Code,Name,State,Owner,Latitude,Longitude,Kind,Size,Difficulty,Terrain,Status,HiddenDate,Founds,NotFounds,Favourites,Altitude\n");

    // Escrever informações de cada geocache no arquivo CSV
    for (int i = 0; i < cachesLoaded; i++) {
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

    printf("\nData saved successfully.\n");
}

// Função para exibir a tabela M81 com cabeçalhos para linhas e colunas
void M81(const Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches loaded.\n");
        return;
    }

    // Initialize a 9x9 matrix to store counts for each difficulty/terrain combination
    int matrix81[9][9] = {0};

    // Fill the matrix with counts
    for (int i = 0; i < cachesLoaded; i++) {
        int difficultyIndex = (geocaches[i].difficulty - 1) * 2;
        int terrainIndex = (geocaches[i].terrain - 1) * 2;
        matrix81[difficultyIndex][terrainIndex]++;
    }

    // Exibir a tabela M81 com cabeçalhos
    printf("\nM81 Table (Difficulty x Terrain):\n");

    // Exibir cabeçalhos de coluna
    printf("    | 1.0  1.5  2.0  2.5  3.0  3.5  4.0  4.5  5.0\n");
    printf("---------------------------------------------\n");

    // Exibir linhas com cabeçalhos
    for (int i = 0; i < 9; i++) {
        printf("%2.1f |", 0.5 * (i + 2)); // Exibir cabeçalho da linha

        // Exibir contagens para cada coluna
        for (int j = 0; j < 9; j++) {
            printf(" %3d ", matrix81[i][j]);
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
void SORT(Cache geocaches[], int cachesLoaded) {
    if (geocaches == NULL || cachesLoaded == 0) {
        printf("\nNo geocaches loaded.\n");
        return;
    }

    int sortOption;

    // Solicitar ao usuário a forma de ordenação
    printf("\nChoose sorting option:\n");
    printf("1 - By altitude (descending)\n");
    printf("2 - By state (A-Z, tiebreaker by founds descending)\n");
    printf("3 - By hidden_date (most recent to oldest)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &sortOption);

    // Realizar a ordenação com base na escolha do usuário
    switch (sortOption) {
        case 1:
            qsort(geocaches, cachesLoaded, sizeof(Cache), compareByAltitude);
            break;
        case 2:
            qsort(geocaches, cachesLoaded, sizeof(Cache), compareByState);
            break;
        case 3:
            qsort(geocaches, cachesLoaded, sizeof(Cache), compareByHiddenDate);
            break;
        default:
            printf("\nInvalid sorting option.\n");
            return;
    }

    // Exibir a listagem ordenada
    printf("\nSorted Geocache Listing:\n");
    for (int i = 0; i < cachesLoaded; i++) {
        printGeocacheDetails(geocaches[i], i);
    }
}