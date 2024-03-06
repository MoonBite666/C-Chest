#include <stdbool.h>
#include "game.h"
#include "menu.h"
#include "music.h"
#include "display.h"
#include "maps.h"
#include "save.h"
#include "define.h"
#include "undo.h"


extern int map[1][15][15];
extern int player[2];
extern int crt_stage;
extern int farthest;
extern WORD ground_color[5];
extern char stage_name[5][20];

static COORD coord = {0,0};
static Stack undo_stack;

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
    system("cls");
    if(stage > 5) return;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, ground_color[stage]);
    
    int crt_map[15][15];
    bool saved = false;
    if(stage < 0) saved = Read_map(crt_map);
    if(saved != true){
        if(stage == 0){//New game
            crt_stage = 0;
            Generate_map(crt_map, 0);
        }
        else{
            stage = farthest;
            Generate_map(crt_map, stage);
        }
        
    }
    Stack_Init(&undo_stack);
    while(1){
        if(Map_cycle(crt_map)){
            SetConsoleTextAttribute(hConsole, BLACK);
            return;
        }
    }
    
}

bool Map_cycle(int *crt_map){
    printf("Stage %d : %s\n",crt_stage, stage_name[crt_stage]);
    bool win = true;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            int data = *((crt_map+i*COL) + j);

            Display_data(data); // Display the data

            if(data == -1 || data == -2){
                player[0] = i;
                player[1] = j;
            } //Mark player's position

            if(data == 2) win = false; // Check if win
        }
        printf("\n");
    }
    printf("Press \"Arrow Keys (← → ↑ ↓)\" to move\nPress Key \"Z\" to Undo the last step. \n");
    printf("Press \"ESC\" to open the menu\n");
    Stack_Push(&undo_stack, crt_map);
    if(win){
        printf("You win!\nPress Enter to the next stage!\n");
        crt_stage++;
        farthest = crt_stage;
        int ch = getch();
        if(ch == 13){//Enter
            Stack_Destroy(&undo_stack);
            Load(crt_stage);
            return 1;
        }
        return 1;
    }
    
    if(Next_frame(crt_map)) return 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

void Undo_map(int* crt_map) {
    int** last_map = Stack_Pop(&undo_stack);
    if (last_map != NULL) {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                int data = last_map[i][j];
                *((crt_map+i*COL) + j) = data;
            }
        }
    }
}
    


bool Next_frame(int *crt_map)
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
    if(ch == 27){//ESC
        int ch1 = 0;
        while(1){
            system("cls");
            Menu_ingame(ch1);
            if(Select(&ch1,4)){
                switch(ch1){
                    case 0:
                        Generate_map(crt_map, crt_stage);
                        break;
                    case 1:
                        return 0;
                    case 2:
                        Save_map(crt_map);
                        break;
                    case 3:
                        return 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    if(ch == 122){//Undo feature
        Undo_map(crt_map);
    }
    return 0;
}