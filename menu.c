#include "menu.h"
void Menu(int state){
    if(state == 0) printf("->");
    printf("\tStart\n");
    if(state == 1) printf("->");
    printf("\tContinue\n"); 
    if(state == 2) printf("->");
    printf("\tExit\n");
}

void SelectBeep(void* data) {
    Beep(1000, 100);
    _endthread();
}