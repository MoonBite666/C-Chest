#define UNUSED(x) (void)(x)
#include <windows.h>
#include <process.h>
#include "music.h"
#include "define.h"

#pragma comment(lib, "winmm.lib")

HRSRC hRes;
HGLOBAL hMem;
DWORD dwSize;
void* pMem;

void Init_rc(){
    hRes = FindResource(NULL, MAKEINTRESOURCE(BGM_WAV), RT_RCDATA);
    hMem = LoadResource(NULL, hRes);
    dwSize = SizeofResource(NULL, hRes);
    pMem = LockResource(hMem);
}

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

void GameBGM(const void* data){
    UNUSED(data);
    PlaySound((LPCSTR)pMem, NULL, SND_MEMORY | SND_ASYNC | SND_LOOP);
    _endthread();
}