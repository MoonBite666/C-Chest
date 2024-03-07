#include "save.h"
#include "menu.h"

extern char stage_name[MAX_STAGE][20];
extern int farthest;
extern int best_step[MAX_STAGE];

void Menu(int state){
    printf("\t┏━╸   ┏━╸╻ ╻┏━╸┏━┓╺┳╸\n\t┃  ╺━╸┃  ┣━┫┣╸ ┗━┓ ┃ \n\t┗━╸   ┗━╸╹ ╹┗━╸┗━┛ ╹ \n");
    if(state == 0) printf("->");
    printf("\t        开始\n");
    if(state == 1) printf("->");
    printf("\t        继续\n"); 
    if(state == 2) printf("->");
    printf("\t        关卡\n");
    if(state == 3) printf("->");
    printf("\t        退出\n");
}



void Menu_stage(int state){
    printf("选择关卡\n");
    if(state == 0) printf("->");
    printf("关卡 0 : %s Best step: %d\n", stage_name[0], best_step[0]);
    if(state == 1 && farthest >= 1){
        printf("->");
    }else if(state == 1) printf(" X ");
    printf("关卡 1 : %s Best step: %d\n", stage_name[1], best_step[1]);
    if(state == 2 && farthest >= 2){
        printf("->"); 
    }else if(state == 2) printf(" X ");
    printf("关卡 2 : %s  Best step: %d\n", stage_name[2], best_step[2]);
    if(state == 3 && farthest >= 3){
        printf("->"); 
    }else if(state == 3) printf(" X ");
    printf("关卡 3 : %s  Best step: %d\n", stage_name[3], best_step[3]);
    if(state == 4 && farthest >= 4){
        printf("->");
    }else if(state == 4) printf(" X ");
    printf("关卡 4 : %s  Best step: %d\n", stage_name[4], best_step[4]);
    if(state == 5) printf("->");
    printf("Back\n");
}

void Menu_ingame(int state){
    printf(" \u25fc Select the menu\n");
    if(state == 0) printf("->");
    printf("\tRestart\n");
    if(state == 1) printf("->");
    printf("\tContinue\n");
    if(state == 2) printf("->");
    printf("\tSave\n");
    if(state == 3) printf("->");
    printf("\tExit\n");
}