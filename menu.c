#include "menu.h"
void menu(int state){
    if(state == 0) printf("->");
    printf("\tStart\n");
    if(state == 1) printf("->");
    printf("\tContinue\n"); 
    if(state == 2) printf("->");
    printf("\tExit\n");
}