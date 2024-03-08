#include "menu.h"
#include "game.h"
#include "music.h"
#include "display.h"
extern int crt_stage;
extern int farthest;

extern HRSRC hRes;
extern HGLOBAL hMem;
extern DWORD dwSize;
extern void* pMem;

static int tmp_map[15][15];
static COORD coord = {0,0};

int state = 0;
int ch = 0;
int main(){
    Init_rc();
    SetConsoleOutputCP(CP_UTF8);
    _beginthread(GameBGM, 0, NULL);
    while(1){
        system("cls");
        Menu(ch);
        bool saved = Read_map(tmp_map);
        if(Select(&ch,4)){//Enter
            switch(ch){
                case 0:
                    Load(0);
                    break;
                case 1:
                    if(saved == true) Load(-1);
                    else Load(farthest);
                    break;
                case 2://Stage Menu
                    int ch1 = 0;
                    bool endmenu = 0;
                    while(endmenu != 1){
                        system("cls");
                        Menu_stage(ch1);
                        if(Select(&ch1,6)){
                            switch(ch1){
                                case 0:
                                    Load(0);
                                    break;
                                case 1:
                                    if(farthest >= 1) Load(1);
                                    else _beginthread(FailedBeep, 0, NULL);
                                    break;
                                case 2:
                                    if(farthest >=2) Load(2);
                                    else _beginthread(FailedBeep, 0, NULL);
                                    break;
                                case 3:
                                    if(farthest >=3) Load(3);
                                    else _beginthread(FailedBeep, 0, NULL);
                                    break;
                                case 4:
                                    if(farthest >=4) Load(4);
                                    else _beginthread(FailedBeep, 0, NULL);
                                    break;
                                case 5:
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