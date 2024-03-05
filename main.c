#include "menu.h"
#include "game.h"
#include "save.h"
#include "music.h"
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
                case 2:
                    int ch1 = 0;
                    while(1){
                        system("cls");
                        Menu_select(crt_stage, ch1);
                        if(Select(&ch1,4)){
                            if(ch1 == 3) break;
                            else{
                                break;//todo
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