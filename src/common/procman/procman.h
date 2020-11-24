#pragma once
#include <stdint.h>
#include <arch/amd64/paging/paging.h>
#include <common/std/llist.h>

llist_t process_list;

struct process {
    process_t* parent;
    uint16_t pid;
    uint16_t userid;
    paging_ctx_t* pg_ctx;
    char* exec;
    char* run_dir;
    char* cmd_line;
    llist_t* tasks;
    llist_t* child_proc;
};
typedef struct process process_t;

process_t* process_create(char* exec, char* root_dir, char* cmd_line, uint16_t userid);
void process_end(process_t* proc);
process_t* process_from_pid(uint16_t pid);
void fork();
void exit(int val);
process_t* process_current();
uint16_t process_create_pid();