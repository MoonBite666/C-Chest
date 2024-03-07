
#include <stdbool.h>
#include "save.h"
void Generate_map(int *crt_map, int stage);
void Init_timer();
void Load(int stage);
bool Select(int *sel, int row);
bool Next_frame(int *crt_map);

void Move_player(int *crt_map, int player_pos, int target_pos);
void Move_chest(int *crt_map, int chest_pos, int target_pos);
void Move(int target, int *crt_map, int dir);
bool Movable(int target, int target_behind);
bool Map_cycle(int *crt_map);

bool Checkwin(int *map);
void Undo_command(int *crt_map, Stack *s);