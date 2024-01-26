#define MAX_CODES 2000

typedef struct {
    char *code;
    char *name;
    char *state;
    char *owner;
    double latitude;
    double longitude;
    char *kind;
    char *size;
    double difficulty;
    double terrain;
    char *status;
    char *hidden_date;
    int founds;
    int not_found;
    int favourites;
    int altitude;
} Cache;



void getGeocaches(const char file[], Cache geocaches[], int *cachesLoaded);
void clearCaches(int *cachesLoaded);
void listGeocaches(const Cache geocaches[], int cachesLoaded);
void loadFile(const char file[], Cache geocaches[], int *cachesLoaded);
void foundPGeocaches(const Cache geocaches[], int cachesLoaded);
void searchGeocache(const Cache geocaches[], int geocacheCount);
void editGeocache(Cache *geocaches, int cachesLoaded);
void center(const Cache geocaches[], int cachesLoaded);
void SORT(Cache geocaches[], int cachesLoaded);
void M81(const Cache geocaches[], int cachesLoaded);
void SAVE(const Cache geocaches[], int cachesLoaded);
void STATEC(const Cache geocaches[], int cachesLoaded);