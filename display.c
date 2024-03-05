#define WALL 1
#define ROAD 0
#define CHEST 2
#define GOAL 3
#define PLAYER -1
#define GOALCHEST 4
#define GOALPLAYER -2

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
        default:
            break;
    }

}