

#include "menu.h"
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



void Menu_select(int farthest, int state){
    printf("Select the stage\n");
    if(state == 0) printf("->");
    printf("Stage 0 : Initial Test\n");
    if(state == 1){
        if(farthest >= 1) printf("->"); else printf(" X ");
    }
    printf("Stage 1 : 1 Test\n");
    if(state == 2){
        if(farthest >= 2) printf("->"); else printf(" X ");
    }
    printf("Stage 2 : 2 Test\n");
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