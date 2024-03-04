#include "menu.h"

int main(){
    // while(1){
    //     menu();
    // }
    int ch;
    while ((ch = getch()) != 'q') {
        switch(ch) {
            case 72:
                printf("Up arrow key pressed\n");
                break;
            case 80:
                printf("Down arrow key pressed\n");
                break;
            case 75:
                printf("Left arrow key pressed\n");
                break;
            case 77:
                printf("Right arrow key pressed\n");
                break;
            default:
                break;
        }
    }
    return 0;
}