#include "maps.h"

int map[2][15][15] = {
    // 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    // 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    // 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 3, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 2, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, -1, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9,
    // 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9,
    // 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
    // 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
    // 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,

    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9,
    9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 8, 9, 9, 1, 3, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 1, 0, 1, 1, 1, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 2, 0, 2, 3, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 3, 0, 2, -1, 1, 1, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 1, 2, 1, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 1, 3, 1, 9, 9, 9, 9, 9, 9,
    9, 8, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 8, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 8, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,

    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 1, -1,0, 0, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 1, 0, 2, 2, 1, 9, 1, 1, 1, 9, 9, 9, 
    9, 9, 9, 1, 0, 2, 0, 1, 9, 1, 3, 1, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 0, 1, 1, 1, 3, 1, 9, 9, 9,
    9, 9, 9, 9, 1, 1, 0, 0, 0, 0, 3, 1, 9, 9, 9,
    9, 9, 9, 9, 1, 0, 0, 0, 1, 0, 0, 1, 9, 9, 9,
    9, 9, 9, 9, 1, 0, 0, 0, 1, 1, 1, 1, 9, 9, 9,
    9, 9, 9, 9, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

int player[2];
WORD map_color[5] = {FOREGROUND_RED | FOREGROUND_GREEN,
 FOREGROUND_GREEN, 
 FOREGROUND_BLUE, 
 FOREGROUND_RED | FOREGROUND_GREEN, 
 FOREGROUND_RED | FOREGROUND_BLUE};
