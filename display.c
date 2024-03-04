#include <stdio.h>
#include <stdlib.h>
#include "display.h"


void Display_data(int data){
    
    switch(data){
        case 1:
            printf("\u26AA");
            break;
        case 0:
            printf("\u2B1C");
            break;
        case -1:
            printf("\u2B50");
            
            break;
        case 2:
            printf("\u2B1B");
            break;
        case 3:
            printf("\u2B55");
            break;
        default:
            break;
    }

}