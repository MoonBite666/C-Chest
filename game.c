#include <stdbool.h>
#include "game.h"
#include "menu.h"
#include "music.h"
#include "display.h"
#include "maps.h"
#include "define.h"

extern int map[MAX_STAGE][15][15];
extern int player[2];
extern int crt_stage;
extern int farthest;
extern int crt_step[MAX_STAGE];
extern int best_step[MAX_STAGE];
extern WORD ground_color[MAX_STAGE];
extern char stage_name[MAX_STAGE][20];



static COORD coord = {0,0};
static Stack history_command;

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
    Stack_destroy(&history_command);
    Stack_init(&history_command);

    system("cls");
    if(stage > 5) return;//any new game mode can be added here
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
            Display_data(data);
            if(data == -1 || data == -2){
                player[0] = i;
                player[1] = j;
            }
            if(data == 2) win = false;
            
        }
        printf("\n");
    }
    printf("Use \"Arrow Keys\" to move;\nuse CTRL+Z to Undo the last step. \n");
    printf("Press ESC to open the menu.\n");
    printf("Your step: %d\n", crt_step[crt_stage]);
    if(win){
        printf("You win!\nPress Enter to the next stage!\n");
        Updata_step();
        printf("Your step: %d, Your best step: %d\n", crt_step[crt_stage], best_step[crt_stage]);
        crt_stage++;
        farthest = crt_stage;
        int ch = getch();
        if(ch == 13){//Enter
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

void Move_chest(int *crt_map, int chest_pos, int target_pos){
    *(crt_map+target_pos) = (*(crt_map+target_pos)==GOAL)?GOALCHEST:CHEST;
    *(crt_map+chest_pos) = (*(crt_map+chest_pos)==GOAL || *(crt_map+chest_pos)==GOALCHEST)?GOAL:ROAD;
}

void Move_player(int *crt_map, int player_pos, int target_pos){
    *(crt_map+target_pos) = (*(crt_map+target_pos)==GOAL)?GOALPLAYER:PLAYER;
    *(crt_map+player_pos) = (*(crt_map+player_pos)==GOALPLAYER)?GOAL:ROAD;
}

void Move(int target, int *crt_map, int dir){
    Command command;
    command.dir = dir;
    command.target = target;
    Stack_push(&history_command, command);//Add command history
    crt_step[crt_stage]++;
    switch(dir){
        case 0://DOWN
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) Move_chest(crt_map, target, target+COL);
            Move_player(crt_map, target-COL, target);
            break;
        case 1://UP
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) Move_chest(crt_map, target, target-COL);
            Move_player(crt_map, target+COL, target);
            break;
        case 2://LEFT
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) Move_chest(crt_map, target, target-1);
            Move_player(crt_map, target+1, target);
            break;
        case 3://RIGHT
            if(*(crt_map+target) == CHEST || *(crt_map+target) == GOALCHEST) Move_chest(crt_map, target, target+1);
            Move_player(crt_map, target-1, target);
            break;
        default:
            break;
    }
    _beginthread(&MoveBeep, 0, NULL);
}

bool Next_frame(int *crt_map)
{
    int ch = getch();
    int addr = player[0]*COL + player[1];
    if(ch == 224){//Arrow
        ch = getch();
        if(ch == DOWN){
            if(Movable(*(crt_map+addr+COL), *(crt_map+addr+COL*2))) Move(addr+COL, crt_map, 0);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == UP){
            if(Movable(*(crt_map+addr-COL), *(crt_map+addr-COL*2))) Move(addr-COL, crt_map, 1);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == LEFT){
            if(Movable(*(crt_map+addr-1), *(crt_map+addr-2))) Move(addr-1, crt_map, 2);
            else _beginthread(&FailedBeep, 0, NULL);
        }
        if(ch == RIGHT){
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
    if(ch == 122){//Undo
        Undo_command(crt_map, &history_command);
    }
    return 0;
}

void Undo_command(int *crt_map, Stack *s){
    Command last_command = Stack_pop(s);
    int dir = last_command.dir;
    int target = last_command.target;
    switch(dir){
        case 0://Last time: DOWN
            Move_player(crt_map, target, target-COL);
            if(*(crt_map+target+COL) == CHEST || *(crt_map+target+COL) == GOALCHEST){
                Move_chest(crt_map, target+COL, target);
            }
            break;
        case 1://Last time: UP
            Move_player(crt_map, target, target+COL);
            if(*(crt_map+target-COL) == CHEST || *(crt_map+target-COL) == GOALCHEST){
                Move_chest(crt_map, target-COL, target);
            }
            break;
        case 2://Last time: LEFT
            Move_player(crt_map, target, target+1);
            if(*(crt_map+target-1) == CHEST || *(crt_map+target-1) == GOALCHEST){
                Move_chest(crt_map, target-1, target);
            }
            break;
        case 3://Last time: RIGHT
            Move_player(crt_map, target, target-1);
            if(*(crt_map+target+1) == CHEST || *(crt_map+target+1) == GOALCHEST){
                Move_chest(crt_map, target+1, target);
            }
            break;
        default:
            break;
    }
    //Add undo se here
    
}