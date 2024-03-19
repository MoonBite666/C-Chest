
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "maps.h"
#include "save.h"

extern WORD ground_color[MAX_STAGE];
extern WORD void_color[MAX_STAGE];
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
            printf("##");
            break;
        case ROAD:
            printf("  ");
            break;
        case PLAYER:
            printf("人");
            break;
        case CHEST:
            printf("箱");
            break;
        case GOAL:
            printf("目");
            break;
        case GOALCHEST:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED, "箱");
            break;
        case GOALPLAYER:
            printf("人");
            break;
        case VOIDBLOCK:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), void_color[crt_stage], "--");
            break;
        case EIGHTSTAR:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW, "星");
            break;
        case FISH:
            printf("鱼");
            break;
        case SHIP:
            printf("船");
            break;
        case OCTOPUS:
            printf("章");
            break;
        case WAVE:
            printf("浪");
            break;
        case CACTUS:
            printf("仙");
            break;
        case PALM:
            printf("榈");
            break;
        case BLOSSOM:
            printf("花");
            break;
        case FIRE:
            printf("火");
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