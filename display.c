
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "maps.h"
#include "save.h"

extern WORD map_color[5];
extern int crt_stage;


void Init_display(HANDLE *hOutput, HANDLE *hOutBuf){
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);

    hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, 
        CONSOLE_TEXTMODE_BUFFER, 
        NULL
    );

    SetConsoleActiveScreenBuffer(hOutBuf);

    // CONSOLE_CURSOR_INFO cci;
    // cci.bVisible=0;
    // cci.dwSize=1;
    // SetConsoleCursorInfo(hOutput, &cci);
    // SetConsoleCursorInfo(hOutBuf, &cci);

}



void Print_colored_text(HANDLE hConsole, WORD color, const char* text) {
    SetConsoleTextAttribute(hConsole, color);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, map_color[crt_stage]); // Reset to stage colors
}

void Set_background_color(HANDLE hConsole, WORD color){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | color);

}


void Display_data(int data){
    
    switch(data){
        case WALL:
            printf("\u26AA");
            break;
        case ROAD:
            printf("\u2B1C");
            break;
        case PLAYER:
            printf("\u2B50");
            break;
        case CHEST:
            printf("\u2B1B");
            break;
        case GOAL:
            printf("\u2B55");
            break;
        case GOALCHEST:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED, "\u2B1B");
            break;
        case GOALPLAYER:
            printf("\u2B50");
            break;
        case VOIDBLOCK:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN, "\u2B1B");
            break;
        case EIGHTSTAR:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED, "\u2728");
            break;
        default:
            break;
    }

}