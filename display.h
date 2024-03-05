#include <windows.h>

void Init_display(HANDLE *hOutput, HANDLE *hOutBuf);

void Display_data(int data);
void Print_colored_text(HANDLE hConsole, WORD color, const char* text);
void Set_background_color(HANDLE hConsole, WORD color);