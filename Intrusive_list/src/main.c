#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *l, int x, int y) {
  struct point *new_el = malloc(sizeof(struct point));
  new_el->x = x;
  new_el->y = y;
  add_node(l, &new_el->node);
}

void remove_point(struct intrusive_list *l, int x, int y) {
  struct intrusive_node *item = l->head;
  while (item) {
    struct point *pt = container_of(item, struct point, node);
    item = item->next;
    if (pt->x == x && pt->y == y) {
      remove_node(l, &pt->node);
      free(pt);
    }
  }
}

void show_all_points(struct intrusive_list *l) {
  for (struct intrusive_node *item = l->head; item; item = item->next) {
    struct point *pt = container_of(item, struct point, node);
    printf("(%d %d)", pt->x, pt->y);
    if (item->next)
      printf(" ");
  }
  printf("\n");
}

void remove_all_points(struct intrusive_list *l) {
  struct intrusive_node *item = l->head;
  while (item) {
    struct point *pt = container_of(item, struct point, node);
    item = item->next;
    remove_node(l, &pt->node);
    free(pt);
  }
}

int main() {
  struct intrusive_list l;
  init_list(&l);
  char command[7];
  while (1) {
    scanf("%6s", command);
    if (!strcmp("add", command)) {
      int x, y;
      scanf("%d", &x);
      scanf("%d", &y);
      add_point(&l, x, y);
    }
    else if (!strcmp("rm", command)) {
      int x, y;
      scanf("%d", &x);
      scanf("%d", &y);
      remove_point(&l, x, y);
    }
    else if (!strcmp("print", command)) {
      show_all_points(&l);
    }
    else if (!strcmp("rma", command)) {
      remove_all_points(&l);
    }
    else if (!strcmp("len", command)) {
      printf("%d\n", get_length(&l));
    }
    else if (!strcmp("exit", command)) {
      remove_all_points(&l);
      break;
    }
    else {
      scanf("%*[^\n]");
      printf("Unknown command\n");
    }
  }
  return 0;
}
