#include <stdbool.h>
#include "define.h"

typedef struct{
    int time;
    bool end;
} Timer;

void Start_timer(Timer *timer);