#include "clist.h"
#include <stdlib.h>

void init_list(struct intrusive_list *l) {
  l->head = NULL;
  l->size = 0;
}

void add_node(struct intrusive_list *l, struct intrusive_node *node) {
  node->prev = NULL;
  node->next = l->head;
  if (l->head)
    l->head->prev = node;
  l->head = node;
  ++l->size;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *node) {
  if (node->next) {
    node->next->prev = node->prev;
  }
  if (node->prev) {
    node->prev->next = node->next;
  }
  else {
    l->head = node->next;
  }
  l->size--;
}

int get_length(struct intrusive_list *l) {
  return l->size;
}

