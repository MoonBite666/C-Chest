#include <stdio.h>
#include <stdlib.h>
#include "save.h"


int crt_stage;
int farthest;

void Save_map(const int *crt_map){
    
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
        printf("Stack is empty!\n");
        Command emptyCommand = {0, 0};
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