#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <common/memory/liballoc.h>

#define LLIST_ITERATE(list, element)    llist_node_t* element = list->first; element != (llist_node_t*)(uintptr_t)0; element = element->next

// This will check that nodes do belong to a list
#define LLIST_DEBUG

#ifdef LLIST_DEBUG
#include <arch/amd64/vga_basic/vga.h>
#endif

struct llist_node {
    void* parent;
    struct llist_node* next;
    struct llist_node* previous;
    void* item;
};
typedef struct llist_node llist_node_t;

struct llist {
    llist_node_t* first;
    llist_node_t* last;
    size_t node_count;
};
typedef struct llist llist_t;

llist_t* llist_create();
void llist_destroy(llist_t* list, bool free_items);
llist_node_t* llist_push_back(llist_t* list, void* item);
llist_node_t* llist_push_front(llist_t* list, void* item);
llist_node_t* llist_insert_before(llist_t* list, llist_node_t* node, void* item);
llist_node_t* llist_insert_after(llist_t* list, llist_node_t* node, void* item);
llist_node_t* llist_insert_before_id(llist_t* list, uintptr_t id, void* item);
llist_node_t* llist_insert_after_id(llist_t* list, uintptr_t id, void* item);
// void llist_swap(llist_t* list, llist_node_t* a, llist_node_t* b);
// void llist_swap_at(llist_t* list, uintptr_t a, uintptr_t b);
void llist_remove(llist_t* list, llist_node_t* node);
void llist_remove_at(llist_t* list, uintptr_t id);
llist_node_t* llist_get_node(llist_t* list, uintptr_t id);
uintptr_t llist_get_id(llist_t* list, llist_node_t* node);


