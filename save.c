#include <stdio.h>
#include "save.h"

int crt_stage;
int farthest;

void Save_map(int *crt_map){
    
    FILE *file;
    file = fopen("save.bin", "wb");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    fwrite(&crt_stage, sizeof(int), 1, file);
    fwrite(crt_map, sizeof(int), COL*ROW, file);

    fclose(file);

    return;
}

bool Read_map(int *crt_map){
    FILE *file;
    file = fopen("save.bin", "rb");
    if (file == NULL) {
        return false;
    }
    fread(&crt_stage, sizeof(int), 1, file);
    fread(crt_map, sizeof(int), COL*ROW, file);

    fclose(file);

    return true;
}