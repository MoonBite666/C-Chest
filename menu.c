#include "save.h"
#include "menu.h"

extern char stage_name[5][20];
extern int farthest;

void Menu(int state){
    //printf(" \u25fd Select the menu\n");
    printf(" \u25fc Select the menu\n");
    //printf(" \u25fb Select the menu\n");
    if(state == 0) printf("->");
    printf("\tStart\n");
    if(state == 1) printf("->");
    printf("\tContinue\n"); 
    if(state == 2) printf("->");
    printf("\tStage\n");
    if(state == 3) printf("->");
    printf("\tExit\n");
}



void Menu_stage(int state){
    printf("Select the stage\n");
    if(state == 0) printf("->");
    printf("Stage 0 : %s\n", stage_name[0]);
    if(state == 1 && farthest >= 1){
        printf("->");
    }else if(state == 1) printf(" X ");
    
    printf("Stage 1 : %s\n", stage_name[1]);
    if(state == 2 && farthest >= 2){
        printf("->"); 
    }else if(state == 2) printf(" X ");
    printf("Stage 2 : %s\n", stage_name[2]);
    if(state == 3) printf("->");
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