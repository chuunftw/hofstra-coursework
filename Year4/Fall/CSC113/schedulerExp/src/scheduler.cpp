#include "scheduler.h"
#include <TimerOne.h>

int item_in_array = 0;
scheduler_element element_list[max_element_size];

bool add_task (int scheduled_time, void (*function_pointer) ()){
    if(item_in_array < max_element_size){
        element_list[item_in_array].scheduled_time = scheduled_time;
        element_list[item_in_array].function_pointer = function_pointer;
        item_in_array++;
        return true;
    }
    else{
        return false;
    } 
}
int tcounter = 0;
#define scheduler_Resolution 1000
#define modulorange 10 
void scheduler_loop(){
    tcounter++; 
    int modcounter = tcounter % modulorange;
    for (int i =0; i<item_in_array; i++){
        if (modcounter == element_list[i].scheduled_time){
            element_list[i].function_pointer
        }
    }
}

void int1_scheduler(){
    Timer1.initialize(scheduler_Resolution);
    Timer1.attachInterrupt(scheduler_loop);
}
