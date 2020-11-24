#include <common/std/llist.h>

llist_t* llist_create() {
    llist_t* list = (llist_t*)malloc(sizeof(llist_t));
    list->first = 0;
    list->last = 0;
    list->node_count = 0;
    return list;
}

void llist_destroy(llist_t* list, bool free_items) {
    llist_node_t* last;
    for (LLIST_ITERATE(list, e)) {
        if (free_items) {
            free(e->item);
        }
        if (e->previous != 0) {
            free(e->previous);
        }
        if (e->next == 0) {
            last = e;
        }
    }
    free(last);
    free(list);
}

llist_node_t* llist_push_back(llist_t* list, void* item) {
    llist_node_t* new_node = (llist_node_t*)malloc(sizeof(llist_node_t));
    new_node->previous = list->last;
    new_node->next = 0;
    new_node->item = item;
    new_node->parent = list;
    if (list->node_count == 0) {
        list->first = new_node;
    }
    else {
        list->last->next = new_node;
    }
    list->last = new_node;
    list->node_count++;
    return new_node;
}

llist_node_t* llist_push_front(llist_t* list, void* item) {
    llist_node_t* new_node = (llist_node_t*)malloc(sizeof(llist_node_t));
    new_node->previous = 0;
    new_node->next = list->first;
    new_node->item = item;
    new_node->parent = list;
    if (list->node_count == 0) {
        list->last = new_node;
    }
    else {
        list->first->previous = new_node;
    }
    list->first = new_node;
    list->node_count++;
    return new_node;
}

llist_node_t* llist_insert_before(llist_t* list, llist_node_t* node, void* item) {
    if (node->parent != list) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to insert before a node that doesn't belong to the right list\n");
#endif
        return (llist_node_t*)~(uintptr_t)0;
    }
    llist_node_t* new_node = (llist_node_t*)malloc(sizeof(llist_node_t));
    new_node->previous = node->previous;
    new_node->next = node;
    new_node->item = item;
    new_node->parent = list;
    if (node->previous != 0) {
        node->previous->next = new_node;
    }
    else {
        list->first = new_node;
    }
    node->previous = new_node;
    list->node_count++;
    return new_node;
}

llist_node_t* llist_insert_after(llist_t* list, llist_node_t* node, void* item) {
    if (node->parent != list) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to insert after a node that doesn't belong to the right list\n");
#endif
        return (llist_node_t*)~(uintptr_t)0;
    }
    llist_node_t* new_node = (llist_node_t*)malloc(sizeof(llist_node_t));
    new_node->previous = node;
    new_node->next = node->next;
    new_node->item = item;
    new_node->parent = list;
    if (node->next != 0) {
        node->next->previous = new_node;
    }
    else {
        list->last = new_node;
    }
    node->next = new_node;
    list->node_count++;
    return new_node;
}

llist_node_t* llist_insert_before_id(llist_t* list, uintptr_t id, void* item) {
    if (id >= list->node_count) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to insert before an id that doesn't belong to the list\n");
#endif
        return (llist_node_t*)~(uintptr_t)0;
    }
    return llist_insert_before(list, llist_get_node(list, id), item);
}

llist_node_t* llist_insert_after_id(llist_t* list, uintptr_t id, void* item) {
    if (id >= list->node_count) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to insert after an id that doesn't belong to the list\n");
#endif
        return (llist_node_t*)~(uintptr_t)0;
    }
    return llist_insert_after(list, llist_get_node(list, id), item);
}


// llist_node_t* llist_swap(llist_t* list, llist_node_t* a, llist_node_t* b);
// llist_node_t* llist_swap_at(llist_t* list, uintptr_t a, uintptr_t b);

void llist_remove(llist_t* list, llist_node_t* node) {
    if (node->parent != list) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to remove a node that doesn't belong to the right list\n");
#endif
        return;
    }
}

void llist_remove_at(llist_t* list, uintptr_t id) {
    if (id >= list->node_count) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to remove an id that doesn't belong to the list\n");
#endif
        return;
    }
}

llist_node_t* llist_get_node(llist_t* list, uintptr_t id) {
    if (id >= list->node_count) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to get a node at an id that doesn't belong to the list\n");
#endif
        return (llist_node_t*)~(uintptr_t)0;
    }
    uintptr_t i = 0;
    for (LLIST_ITERATE(list, e)) {
        if (i != id) {
            i++;
            continue;
        }
        return e;
    }
    return (llist_node_t*)~(uintptr_t)0;
}

uintptr_t llist_get_id(llist_t* list, llist_node_t* node) {
    if (node->parent != list) {
#ifdef LLIST_DEBUG
        vga_print("ERROR: Tried to get the id a node that doesn't belong to the right list\n");
#endif
        return ~0;
    }
    int i = 0;
    for (LLIST_ITERATE(list, e)) {
        if (e != node) {
            i++;
            continue;
        }
        return i;
    }
    return ~0;
}