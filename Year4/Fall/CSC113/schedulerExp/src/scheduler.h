#ifndef SCHEDULER_H
#define SCHEDULER_H

struct scheduler_element{
    int scheduled_time;
    void (*function_pointer) ();

};

#define max_element_size 10
extern scheduler_element element_list[max_element_size];

bool add_task (int scheduled_time, void (*function_pointer) ());

#endif
