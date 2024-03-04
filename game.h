#include <stdbool.h>

void Load(int stage);
bool Select(int *sel, int row);
bool Next_frame(int col,int *map);
void Move(int target, int *map, int dir, int col);
bool Movable(int target, int target_behind);
void Map_cycle(int row, int col,const int *map);
