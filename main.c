#include "menu.h"
#include "game.h"
#include "music.h"
#include "display.h"
extern int crt_stage;
extern int farthest;

static COORD coord = {0,0};

int state = 0;
int ch = 0;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    while(1){
        system("cls");
        Menu(ch);
        
        if(Select(&ch,4)){//Enter
            switch(ch){
                case 0:
                    Load(0);
                    break;
                case 1:
                    Load(-1);
                    break;
                case 2://Stage Menu
                    int ch1 = 0;
                    bool endmenu = 0;
                    while(endmenu != 1){
                        system("cls");
                        Menu_stage(ch1);
                        if(Select(&ch1,4)){
                            switch(ch1){
                                case 0:
                                    Load(0);
                                    break;
                                case 1:
                                    if(farthest >= 1) Load(1);
                                    break;
                                case 2:
                                    if(farthest >=2) Load(2);
                                    break;
                                case 3:
                                    endmenu = 1;
                                    break;
                            }
                        }
                    }
                    break;
                    
                case 3:
                    return 0;
                    break;

            }
        }
    }
    return 0;
}