#include "menu.h"

int state = 0;
int main(){
    while(1){
        system("cls");
        menu(state);
        int ch = getch();
        if(ch == 224){//Arrow
            ch = getch();
            if(ch == 72) state--;
            if(ch == 80) state++;
            if(state < 0) state = 2;
            if(state > 2) state = 0;
        }
        if(ch == 13){//Enter
            
        }
    }
    return 0;
}