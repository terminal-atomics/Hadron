#pragma once
#include <common/memory/liballoc.h>
#include <stdbool.h>
#include <common/scheduler/scheduler.h>

typedef volatile int mutex_t;
// typedef volatile int semaphore_t;

mutex_t* mutex_create();
// semaphore_t* semaphore_create();

void mutex_lock(mutex_t* mtx);
void mutex_spinlock(mutex_t* mtx);
bool mutex_trylock(mutex_t* mtx);
void mutex_unlock(mutex_t* mtx);