#include <common/std/mutex.h>

mutex_t* mutex_create() {
    mutex_t* mtx = (mutex_t*)malloc(sizeof(mutex_t));
    *mtx = 0;
    return mtx;
}

void mutex_lock(mutex_t* mtx) {
    while (!__sync_bool_compare_and_swap(mtx, 0, 1)) {
		scheduler_yield();
	}
}

void mutex_spinlock(mutex_t* mtx) {
    while (!__sync_bool_compare_and_swap(mtx, 0, 1)) {
		asm("pause"); // TODO: Change this for other then x86
	}
}

bool mutex_trylock(mutex_t* mtx) {
    return __sync_bool_compare_and_swap(mtx, 0, 1);
}

void mutex_unlock(mutex_t* mtx) {
    *mtx = 0;
}