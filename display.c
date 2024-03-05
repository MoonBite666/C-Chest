
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
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
            printf("\u2B1C");
            break;
        case GOALPLAYER:
            printf("\u2B50");
            break;
        case VOID:
            printf(" ");
            break;
        default:
            break;
    }

}