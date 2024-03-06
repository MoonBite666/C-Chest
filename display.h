#include <windows.h>

void Display_data(int data);
void Print_colored_text(HANDLE hConsole, WORD color, const char* text);
void Set_background_color(HANDLE hConsole, WORD color);
void Set_display_size(short width, short height);