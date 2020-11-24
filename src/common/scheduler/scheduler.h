#pragma once
#include <arch/amd64/tasking/tasking.h>
#include <common/std/llist.h>
#include <common/std/mutex.h>

struct thread {
    task_t* task;
    llist_node_t* tl_node;
};
typedef struct thread thread_t;

void scheduler_init();
thread_t* scheduler_create_thread(task_t* state);
void scheduler_remove_thread(thread_t* thread);
void scheduler_yield();

// DO NOT CALL IN C, ONLY FROM HANDLER
void scheduler_switch_task();
void scheduler_idle();