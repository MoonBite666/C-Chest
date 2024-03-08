
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
            printf("\xF0\x9F\x9A\xB6");
            break;
        case CHEST:
            printf("📦");
            break;
        case GOAL:
            printf("\xF0\x9F\x8E\xAF");
            break;
        case GOALCHEST:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED, "📦");
            break;
        case GOALPLAYER:
            printf("\xF0\x9F\x9A\xB6");
            break;
        case VOIDBLOCK:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), void_color[crt_stage], "--");
            break;
        case EIGHTSTAR:
            Print_colored_text(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW, "\xF0\x9F\x8C\x9F");
            break;
        case FISH:
            printf("\xF0\x9F\x90\x9F");
            break;
        case SHIP:
            printf("\xE2\x9B\xB5");
            break;
        case OCTOPUS:
            printf("\xF0\x9F\x90\x99");
            break;
        case WAVE:
            printf("\xF0\x9F\x8C\x8A");
            break;
        case CACTUS:
            printf("\xF0\x9F\x8C\xB5");
            break;
        case PALM:
            printf("\xF0\x9F\x8C\xB4");
            break;
        case BLOSSOM:
            printf("\xF0\x9F\x8C\xB8");
            break;
        case FIRE:
            printf("\xF0\x9F\x94\xA5");
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