

#include "game.h"
#include "menu.h"
#include "music.h"
#include "display.h"
#include "maps.h"

void Load(int stage)
{
    while(1){
        switch(stage){
        case 0:
            if(Map_cycle(10, 10, map01)) return;
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        
        }
    }
    
}

bool Map_cycle(int row, int col,const int *map){
    printf("row : %d, col : %d\n", row, col);
    bool win = true;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int data = *((map+i*col) + j);
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
    Next_frame(col, map);
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
        if(target_behind == WALL || target_behind == CHEST || target_behind == GOALCHEST) return false;
    }
    return true;
}

void Move(int target, int *map, int dir, int col){
    switch(dir){
        case 0:
            if(*(map+target) == CHEST || *(map+target) == GOALCHEST) *(map+target+col) = 
            (*(map+target+col)==GOAL)?GOALCHEST:CHEST;
            
            *(map+target) = (*(map+target)==GOAL || *(map+target)==GOALCHEST)?GOALPLAYER:PLAYER;
            *(map+target-col) = (*(map+target-col)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 1:
            if(*(map+target) == CHEST || *(map+target) == GOALCHEST) *(map+target-col) = 
            (*(map+target-col)==GOAL)?GOALCHEST:CHEST;
            *(map+target) = (*(map+target)==GOAL || *(map+target)==GOALCHEST)?GOALPLAYER:PLAYER;
            *(map+target+col) = (*(map+target+col)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 2:
            if(*(map+target) == CHEST || *(map+target) == GOALCHEST) *(map+target-1) = 
            (*(map+target-1)==GOAL)?GOALCHEST:CHEST;
            *(map+target) = (*(map+target)==GOAL || *(map+target) == GOALCHEST)?GOALPLAYER:PLAYER;
            *(map+target+1) = (*(map+target+1)==GOALPLAYER)?GOAL:ROAD;
            break;
        case 3:
            if(*(map+target) == CHEST || *(map+target) == GOALCHEST) *(map+target+1) = 
            (*(map+target+1)==GOAL)?GOALCHEST:CHEST;
            *(map+target) = (*(map+target)==GOAL || *(map+target) == GOALCHEST)?GOALPLAYER:PLAYER;
            *(map+target-1) = (*(map+target-1)==GOALPLAYER)?GOAL:ROAD;
            break;
        default:
            break;
    }
    _beginthread(&MoveBeep, 0, NULL);
}

bool Next_frame(int col, int *map)


{
    int ch = getch();
    int addr = player[0]*col + player[1];
    if(ch == 224){//Arrow
        ch = getch();
        if(ch == 80){//↓
            if(Movable(*(map+addr+col), *(map+addr+col*2))) Move(addr+col, map, 0, col);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 72){ //↑
            if(Movable(*(map+addr-col), *(map+addr-col*2))) Move(addr-col, map, 1, col);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 75){//←
            if(Movable(*(map+addr-1), *(map+addr-2))) Move(addr-1, map, 2, col);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == 77){ //→
            if(Movable(*(map+addr+1), *(map+addr+2))) Move(addr+1, map, 3, col);
            else _beginthread(&FailedBeep, 0, NULL);
        }
    }
}