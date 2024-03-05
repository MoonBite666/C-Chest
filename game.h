
#include <stdbool.h>

void Generate_map(int *crt_map, int stage);
void Load(int stage);
bool Select(int *sel, int row);
void Next_frame(int *crt_map);
void Move(int target, int *crt_map, int dir);
bool Movable(int target, int target_behind);
bool Map_cycle(int *crt_map);

bool Checkwin(int *map);
