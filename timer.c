#include <unistd.h>
#include <process.h>
#include "timer.h"



void Start_timer(Timer *timer){
    while(timer->end != 1){
        timer->time++;
        sleep(1);
    }
}