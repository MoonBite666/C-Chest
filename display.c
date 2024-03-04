#include <stdio.h>

#include "display.h"


void Display_map(int row, int col,int *map){
    
    
    printf("row : %d, col : %d\n", row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){

            printf("%d ", *((map+i*col) + j));

        }
        printf("\n");
    }
    system("pause");
}