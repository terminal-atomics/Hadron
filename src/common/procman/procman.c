#include <common/procman/procman.h>

process_t* process_create(char* exec, char* run_dir, char* cmd_line, uint16_t userid) {
    process_t* proc = malloc(sizeof(process_t));
    proc->exec = strclone(exec);
    proc->run_dir = strclone(run_dir);
    proc->cmd_line = strclone(cmd_line);
    proc->parent = process_current();

    // TODO: Lock pid list to avoid dupes
    proc->pid = process_create_pid();
    proc->pg_ctx = paging_create_context();

}

void process_end(process_t* proc) {
    // Kill all threads
    for (LLIST_ITERATE(proc->tasks, t)) {
        task_t* task = (task_t*)t->item;
        scheduler_remove_task(task);
    }


}

process_t* process_from_pid(uint16_t pid) {

}

void fork() {

}

void exit(int val) {
    
}