#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "point_list.h"

void load_text(char *strname, intrusive_list *list) {
    FILE *in = fopen(strname, "r");
    assert(in);
    int x, y;
    while (fscanf(in, "%d %d", &x, &y) == 2)
        add_point(list, x, y);
    fclose(in);
}

void save_text(char *strname, intrusive_list *list) {
    FILE *out = fopen(strname, "w");
    assert(out);
    for (intrusive_node *item = list->head.next; item != &list->head; item = item->next) {
        fprintf(out, "%d %d\n", get_point(item)->x, get_point(item)->y);
    }
    fclose(out);
}

void print(intrusive_node *node, void *data) {
    assert(node);
    assert(data);
    printf((char *)data, get_point(node)->x, get_point(node)->y);
}

void count(intrusive_node *node, void *data) {
    assert(node);
    assert(data);
    (*(int *)data)++;
}

void load_bin(char *strname, intrusive_list *list) {
    FILE *in = fopen(strname, "rb");
    assert(in);
    unsigned char new_x;
    while (fread(&new_x, 1, 1, in)) {
        int x = 0, y = 0;
        unsigned char new_y;
        x += new_x;
        fread(&new_x, 1, 1, in);
        x += 256 * (int)new_x;
        fread(&new_x, 1, 1, in);
        x += 256 * 256 * (int)new_x;
        fread(&new_y, 1, 1, in);
        y += new_y;
        fread(&new_y, 1, 1, in);
        y += 256 * (int)new_y;
        fread(&new_y, 1, 1, in);
        y += 256 * 256 * (int)new_y;
        add_point(list, x, y);
    }
    fclose(in);
}

void save_bin(char *strname, intrusive_list *list) {
    FILE *out = fopen(strname, "wb");
    assert(out);
    for (intrusive_node *item = list->head.next; item != &list->head; item = item->next) {
        int x = 0, y = 0, new_x, new_y;
        x = get_point(item)->x;
        y = get_point(item)->y;
        for (int i = 0; i < 3; i++) {
            new_x = x % 256;
            x /= 256;
    	    fwrite(&new_x, 1, 1, out);
        }
        for (int i = 0; i < 3; i++) {
    	    new_y = y % 256;
    	    y /= 256;
    	    fwrite(&new_y, 1, 1, out);
        }
    }
    fclose(out);
}

int main(int argc, char *argv[]) {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);
     
    assert(argc >= 4 && argc <= 5);

    if (strcmp(argv[1], "loadtext") == 0) {
        load_text(argv[2], l);
    }
    else if (strcmp(argv[1], "loadbin") == 0) {
        load_bin(argv[2], l);
    }
    else assert(!"This command is not supported");
  
    if (strcmp(argv[3], "print") == 0) {
        assert(argv[4]);
        apply(l, print, argv[4]);
        printf("\n");
    }
    else if (strcmp(argv[3], "count") == 0) {
        int cnt = 0;
        apply(l, count, &cnt);
        printf("%d\n", cnt);
    }
    else if (strcmp(argv[3], "savetext") == 0) {
      assert(argv[4]);
      save_text(argv[4], l);
    }
    else if (strcmp(argv[3], "savebin") == 0) {
        assert(argv[4]);
        save_bin(argv[4], l);
    }
    else assert(!"This command is not supported");
    remove_all_points(l);
  
    return 0;
}
