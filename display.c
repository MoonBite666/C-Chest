
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "maps.h"
#include "save.h"

extern WORD ground_color[5];
extern WORD void_color[5];
extern int crt_stage;

void Print_colored_text(HANDLE hConsole, WORD color, const char* text) {
    SetConsoleTextAttribute(hConsole, color);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, ground_color[crt_stage]); // Reset to stage colors
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
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), void_color[crt_stage], "\u2B1B");
            break;
        case EIGHTSTAR:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED, "\u2728");
            break;
        default:
            break;
    }

}

void Set_display_size(short width, short height){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the screen buffer size
    COORD coord = {width, height};
    SetConsoleScreenBufferSize(hConsole, coord);

    // Set the window size
    SMALL_RECT rect = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}