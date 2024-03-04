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
            Map_cycle(10, 10, map01);
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

void Map_cycle(int row, int col,const int *map){
    printf("row : %d, col : %d\n", row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int data = *((map+i*col) + j);
            Display_data(data);
            if(data == -1){
                player[0] = i;
                player[1] = j;
            }
            
        }
        printf("\n");
    }
    Next_frame(col, map);
    system("cls");
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
    if(target == 1) return false;
    if(target == 2){
        if(target_behind == 1 || target_behind == 2) return false;
    }
    return true;
}

void Move(int target, int *map, int dir, int col){
    switch(dir){
        case 0:
            if(*(map+target) == 2) *(map+target+col) = 2;
            *(map+target) = -1;
            *(map+target-col) = 0;
            break;
        case 1:
            if(*(map+target) == 2) *(map+target-col) = 2;
            *(map+target) = -1;
            *(map+target+col) = 0;
            break;
        case 2:
            if(*(map+target) == 2) *(map+target-1) = 2;
            *(map+target) = -1;
            *(map+target+1) = 0;
            break;
        case 3:
            if(*(map+target) == 2) *(map+target+1) = 2;
            *(map+target) = -1;
            *(map+target-1) = 0;
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