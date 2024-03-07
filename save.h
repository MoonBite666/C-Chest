#include <stdbool.h>
#include "define.h"
typedef struct {
    int target;
    int dir;
    bool chest;
} Command;

typedef struct {
    Command* arr;
    int top;
} Stack;


void Save_map(const int *crt_map);
bool Read_map(int *crt_map);
void Updata_step();

void Stack_init(Stack* s);
int Stack_isEmpty(const Stack* s);
int Stack_isFull(const Stack* s);
void Stack_push(Stack* s, Command value);
Command Stack_pop(Stack* s);
void Stack_destroy(Stack* s);