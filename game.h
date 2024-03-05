#define WALL 1
#define ROAD 0
#define CHEST 2
#define GOAL 3
#define PLAYER -1
#define GOALCHEST 4
#define GOALPLAYER -2

#include <stdbool.h>

void Load(int stage);
bool Select(int *sel, int row);
bool Next_frame(int col,int *map);
void Move(int target, int *map, int dir, int col);
bool Movable(int target, int target_behind);
bool Map_cycle(int row, int col,const int *map);

bool Checkwin(int *map);
