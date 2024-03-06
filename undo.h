#include "define.h"
typedef struct {
    int*** arr;
    int top;
} Stack;

void Stack_Init(Stack* s);
int Stack_IsEmpty(Stack* s);
int Stack_IsFull(Stack* s);
void Stack_Push(Stack* s, int* value);
int** Stack_Pop(Stack* s);
void Stack_Destroy(Stack* s);