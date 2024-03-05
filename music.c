#define UNUSED(x) (void)(x)
#include <windows.h>
#include <process.h>
#include "music.h"

void SelectBeep(const void* data) {
    UNUSED(data);
    Beep(800, 20);
    Beep(1000, 20);
    _endthread();
}

void MoveBeep(const void* data){
    UNUSED(data);
    Beep(500, 50);
    _endthread();
}
void FailedBeep(const void* data){
    UNUSED(data);
    Beep(1000, 25);
    Beep(500, 25);
    _endthread();
}

void MenuMusic(const void* data){
    UNUSED(data);
    Beep(800, 100);
    Beep(1000, 100);
    Beep(1200, 100);
    Beep(1500, 100);
    Beep(1800, 100);
    Beep(2000, 100);
    Beep(1800, 100);
    Beep(1500, 100);
    Beep(1200, 100);
    Beep(1000, 100);
    Beep(800, 100);
    _endthread();
}