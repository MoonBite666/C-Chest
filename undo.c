#include "undo.h"

#include <stdio.h>
#include <stdlib.h>


void Stack_Init(Stack* s) {
    s->arr = (int***)malloc(MAXUNDO * sizeof(int**));
    for (int i = 0; i < MAXUNDO; i++) {
        s->arr[i] = (int**)malloc(ROW * sizeof(int*));
        for (int j = 0; j < ROW; j++) {
            s->arr[i][j] = (int*)malloc(COL * sizeof(int));
        }
    }
    s->top = -1;
}

int Stack_IsEmpty(Stack* s) {
    return s->top == -1;
}

int Stack_IsFull(Stack* s) {
    return s->top == MAXUNDO - 1;
}

void Stack_Push(Stack* s, int* value) {
    if (Stack_IsFull(s)) {
        printf("Stack is full!\n");
        return;
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            int data = *((value+i*COL) + j);
            s->arr[s->top + 1][i][j] = data;
        }
    }
    s->top++;
}

int** Stack_Pop(Stack* s) {
    if (Stack_IsEmpty(s)) {
        printf("Stack is empty!\n");
        return NULL;
    }
    return s->arr[s->top--];
}

void Stack_Destroy(Stack* s) {
    for (int i = 0; i < MAXUNDO; i++) {
        for (int j = 0; j < ROW; j++) {
            free(s->arr[i][j]);
        }
        free(s->arr[i]);
    }
    free(s->arr);
}


// int main() {
//     Stack s;
//     Stack_Init(&s);
//     int** matrix = (int**)malloc(ROW * sizeof(int*));
//     for (int i = 0; i < ROW; i++) {
//         matrix[i] = (int*)malloc(COL * sizeof(int));
//         for (int j = 0; j < COL; j++) {
//             matrix[i][j] = i * COL + j;
//         }
//     }
//     Stack_Push(&s, matrix);
//     int** popped_matrix = Stack_Pop(&s);
//     for (int i = 0; i < ROW; i++) {
//         for (int j = 0; j < COL; j++) {
//             printf("%d ", popped_matrix[i][j]);
//         }
//         printf("\n");
//     }
//     Stack_Destroy(&s);
//     for (int i = 0; i < ROW; i++) {
//         free(matrix[i]);
//     }
//     free(matrix);
//     return 0;
// }