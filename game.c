#include "game.h"
#include "menu.h"
#include "display.h"
#include "maps.h"

void Load(int stage)
{
    switch(stage){
        case 0:
            Display_map(10, 10, map01);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    //todo
}

bool Select(int *sel, int row)
{
    int ch = getch();
    if(ch == 224){//Arrow
        _beginthread(SelectBeep, 0, NULL);
        ch = getch();
        if(ch == 72) (*sel)--;
        if(ch == 80) (*sel)++;
        if((*sel) < 0) (*sel) = row-1;
        if((*sel) > row-1) (*sel) = 0;
    }
    if(ch == 13){//Enter
        return true;
    }
    return false;
}
