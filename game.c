#define ROW 15
#define COL 15

#include "game.h"
#include "menu.h"
#include "music.h"
#include "display.h"
#include "maps.h"

void Generate_map(int *crt_map, int stage)
{
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            *(crt_map+i*COL + j) = map[stage][i][j];
        }
    }
}

void Load(int stage)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE);
    int crt_map[15][15];
    Generate_map(crt_map, stage);
    while(1){
        if(Map_cycle(crt_map)){
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        }

        
    }
    
}

bool Map_cycle(int *crt_map){
    printf("row : %d, col : %d\n", ROW, COL);
    bool win = true;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            int data = *((crt_map+i*COL) + j);
            Display_data(data);
            if(data == -1 || data == -2){
                player[0] = i;
                player[1] = j;
            }
            if(data == 2) win = false;
            
        }
        printf("\n");
    }
    if(win){
        printf("You win!\n");
        // _beginthread(&WinBeep, 0, NULL);
        system("pause");
        return 1;
    }
    Next_frame(crt_map);
    system("cls");
    return 0;
}



bool Select(int *sel, int row)
{
    int ch = getch();
    if(ch == 224){//Arrow
        _beginthread(&SelectBeep, 0, NULL);
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

bool Movable(int target, int target_behind){
    if(target == WALL) return false;
    if(target == CHEST || target == GOALCHEST){
        if(target_behind == WALL || target_behind == CHEST || target_behind == GOALCHEST){
            return false;
        }
    }
    return true;
}

void Move(int target, int *crt_map, int dir){
    switch(dir){
        case 0:
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) *(crt_map+target+COL) = 
            (*(crt_map+target+COL)==GOAL)?GOALCHEST:CHEST;
            
            *(crt_map+target) = (*(crt_map+target)==GOAL || *(crt_map+target)==GOALCHEST)?GOALPLAYER:PLAYER;
            *(crt_map+target-COL) = (*(crt_map+target-COL)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 1:
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) *(crt_map+target-COL) = 
            (*(crt_map+target-COL)==GOAL)?GOALCHEST:CHEST;
            *(crt_map+target) = (*(crt_map+target)==GOAL || *(crt_map+target)==GOALCHEST)?GOALPLAYER:PLAYER;
            *(crt_map+target+COL) = (*(crt_map+target+COL)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 2:
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) *(crt_map+target-1) = 
            (*(crt_map+target-1)==GOAL)?GOALCHEST:CHEST;
            *(crt_map+target) = (*(crt_map+target)==GOAL || *(crt_map+target) == GOALCHEST)?GOALPLAYER:PLAYER;
            *(crt_map+target+1) = (*(crt_map+target+1)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 3:
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) *(crt_map+target+1) = 
            (*(crt_map+target+1)==GOAL)?GOALCHEST:CHEST;
            *(crt_map+target) = (*(crt_map+target)==GOAL || *(crt_map+target) == GOALCHEST)?GOALPLAYER:PLAYER;
            *(crt_map+target-1) = (*(crt_map+target-1)==GOALPLAYER)?GOAL:ROAD;
            break;
        default:
            break;
    }
    _beginthread(&MoveBeep, 0, NULL);
}

void Next_frame(int *crt_map)
{
    int ch = getch();
    int addr = player[0]*COL + player[1];
    if(ch == 224){//Arrow
        ch = getch();
        if(ch == 80){//↓
            if(Movable(*(crt_map+addr+COL), *(crt_map+addr+COL*2))) Move(addr+COL, crt_map, 0);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 72){ //↑
            if(Movable(*(crt_map+addr-COL), *(crt_map+addr-COL*2))) Move(addr-COL, crt_map, 1);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 75){//←
            if(Movable(*(crt_map+addr-1), *(crt_map+addr-2))) Move(addr-1, crt_map, 2);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 77){ //→
            if(Movable(*(crt_map+addr+1), *(crt_map+addr+2))) Move(addr+1, crt_map, 3);
            else _beginthread(&FailedBeep, 0, NULL);
        }
    }
}