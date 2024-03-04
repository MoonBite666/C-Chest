#define UNUSED(x) (void)(x)
#include <windows.h>
#include <process.h>
#include "music.h"

void SelectBeep(const void* data) {
    UNUSED(data);
    Beep(1000, 100);
    _endthread();
}

void MoveBeep(const void* data){
    UNUSED(data);
    Beep(500, 100);
    _endthread();
}
void FailedBeep(const void* data){
    UNUSED(data);
    Beep(1000, 50);
    Beep(500, 50);
    _endthread();
}