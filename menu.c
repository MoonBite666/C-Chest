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
    printf("\t          选择关卡\n");
    if(state == 0) printf("->");
    printf("\t关卡 0 : %s  最佳步数： %d\n", stage_name[0], best_step[0]);
    if(state == 1 && farthest >= 1){
        printf("->");
    }else if(state == 1) printf(" X ");
    printf("\t关卡 1 : %s  最佳步数： %d\n", stage_name[1], best_step[1]);
    if(state == 2 && farthest >= 2){
        printf("->"); 
    }else if(state == 2) printf(" X ");
    printf("\t关卡 2 : %s  最佳步数： %d\n", stage_name[2], best_step[2]);
    if(state == 3 && farthest >= 3){
        printf("->"); 
    }else if(state == 3) printf(" X ");
    printf("\t关卡 3 : %s  最佳步数： %d\n", stage_name[3], best_step[3]);
    if(state == 4 && farthest >= 4){
        printf("->");
    }else if(state == 4) printf(" X ");
    printf("\t关卡 4 : %s  最佳步数： %d\n", stage_name[4], best_step[4]);
    if(state == 5) printf("->");
    printf("\t         回到主菜单\n");
}

void Menu_ingame(int state){
    printf("\t \u25fc菜单\n");
    if(state == 0) printf("->");
    printf("\t重新开始\n");
    if(state == 1) printf("->");
    printf("\t继续游戏\n");
    if(state == 2) printf("->");
    printf("\t保存游戏\n");
    if(state == 3) printf("->");
    printf("\t退出游戏\n");
}