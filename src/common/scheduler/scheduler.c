#include <common/scheduler/scheduler.h>

llist_t* scheduler_tl;
mutex_t* scheduler_tl_mtx;
task_t* scheduler_it;
uint8_t scheduler_is[512];
llist_node_t* scheduler_current_thread;

void scheduler_init() {
    scheduler_tl = llist_create();
    scheduler_tl_mtx = mutex_create();
    scheduler_it = tasking_prepare_task((uintptr_t)scheduler_idle, (uintptr_t)&scheduler_is[511], (uintptr_t)&scheduler_is[511], &paging_k_ctx, TASK_PRIV_KERNEL);
    scheduler_current_thread = NULL;
}

thread_t* scheduler_create_thread(task_t* state) {
    thread_t* new_thread = (thread_t*)malloc(sizeof(thread_t));
    new_thread->task = state;
    mutex_spinlock(scheduler_tl_mtx);
    new_thread->tl_node = llist_push_back(scheduler_tl, new_thread);
    mutex_unlock(scheduler_tl_mtx);
    return new_thread;
}

void scheduler_remove_thread(thread_t* thread) {
    mutex_spinlock(scheduler_tl_mtx);
    llist_remove(scheduler_tl, thread->tl_node);
    mutex_unlock(scheduler_tl_mtx);
}

void scheduler_yield() {
    tasking_yield();
}

void scheduler_switch_task() {
    // Try to lock threadlist, if not able to lock, continue with same thread
    if (!mutex_trylock(scheduler_tl_mtx)) {
        return;
    }

    // If the thread list is empty, switch to idle task
    if (scheduler_tl->node_count == 0) {
        tasking_current_task = scheduler_it;
        mutex_unlock(scheduler_tl_mtx);
        return;
    }

    // If this is the first time a thread is run, set it up and run
    if (scheduler_current_thread == NULL) {
        thread_t* thread = scheduler_tl->first->item;
        scheduler_current_thread = scheduler_tl->first;
        tasking_current_task = thread->task;
        mutex_unlock(scheduler_tl_mtx);
        return;
    }

    llist_node_t* next = scheduler_current_thread->next;
    // If current task is last, wrap back to the beginning
    if (next == 0) {
        next = scheduler_tl->first;
    }

    // Load next task
    thread_t* thread = next->item;
    tasking_current_task = thread->task;
    scheduler_current_thread = next;

    mutex_unlock(scheduler_tl_mtx);
}

void scheduler_idle() {
    tasking_yield();
}