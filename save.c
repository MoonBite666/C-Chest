#include <stdio.h>
#include <stdlib.h>
#include "save.h"


int crt_stage;
int farthest;

int crt_step[MAX_STAGE] = {0};
int best_step[MAX_STAGE] = {0};

void Save_map(const int *crt_map){
    
    FILE *file;
    file = fopen("save.bin", "wb");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    fwrite(&best_step, sizeof(int), MAX_STAGE, file);
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
    fread(&best_step, sizeof(int), MAX_STAGE, file);
    fread(&farthest, sizeof(int), 1, file);
    fread(crt_map, sizeof(int), COL*ROW, file);
    fclose(file);

    return true;
}


void Stack_init(Stack* s) {
    s->arr = (Command*)malloc(MAX_UNDO * sizeof(Command));
    s->top = -1;
}

int Stack_isEmpty(const Stack* s) {
    return s->top == -1;
}

int Stack_isFull(const Stack* s) {
    return s->top == MAX_UNDO - 1;
}

void Stack_push(Stack* s, Command value) {
    if (Stack_isFull(s)) {
        printf("Stack is full!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

Command Stack_pop(Stack* s) {
    if (Stack_isEmpty(s)) {
        printf("No step to undo!\n");
        Command emptyCommand = {0, -1, 0};
        return emptyCommand;
    }
    return s->arr[(s->top)--];
}

void Stack_destroy(Stack* s) {
    if(s->arr != NULL){
        free(s->arr);
        s->top = -1;
    }
    
}

void Updata_step(){
    if(crt_step[crt_stage] < best_step[crt_stage] || best_step[crt_stage] == 0){
        best_step[crt_stage] = crt_step[crt_stage];
    }
}