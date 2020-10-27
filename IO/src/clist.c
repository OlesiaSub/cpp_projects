#include "clist.h"

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data) {
    for (intrusive_node *item = list->head.next; item != &list->head; item = item->next) {
        op(item, data);
    }
}

void init_list(intrusive_list *list) {
    intrusive_node *head = &list->head;
    head->next = head;
    head->prev = head;
}

void add_node(intrusive_list *list, intrusive_node *node) {
    intrusive_node *last = list->head.prev;
    intrusive_node *head = &list->head;

    node->next = head;
    node->prev = last;

    head->prev = node;
    last->next = node;
}

void remove_node(intrusive_list *list, intrusive_node *node) {
    (void) list;
    intrusive_node *prev = node->prev;
    intrusive_node *next = node->next;

    prev->next = next;
    next->prev = prev;
}

int get_length(intrusive_list *list) {
    int length = 0;
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next)
        ++length;

    return length;
}
