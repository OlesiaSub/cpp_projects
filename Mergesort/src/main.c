#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "mergesort.h"
#include "my_memcpy.h"

int intcmpr(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int strcmpr(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b); 
}

int charcmpr(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}

void print_int(int *arr, int elems) {
  mergesort(arr, elems, sizeof(arr[0]), intcmpr);
  for (int i = 0; i < elems; i++) {
    printf("%d", arr[i]);
    if (i != elems)
      printf(" ");
  }
  printf("\n");
}

void print_char(char *arr, int elems) {
  mergesort(arr, elems, sizeof(arr[0]), charcmpr);
  for (int i = 0; i < elems; i++) {
    printf("%c", arr[i]);
    if (i != elems)
      printf(" ");
  }
  printf("\n");
}

void print_str(char **arr, size_t elems) {
  mergesort(arr, elems, sizeof(arr[0]), strcmpr);
  for (size_t i = 0; i < elems; i++) {
    printf("%s", arr[i]);
    if (i != elems)
      printf(" ");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc <= 2)
    return -1;
  assert(strcmp(argv[0], "int") || strcmp(argv[0], "char") || strcmp(argv[0], "str"));
  if (strcmp(argv[1], "int") == 0) {
    int val[argc - 2];
    for (int i = 2; i < argc; i++)
      val[i - 2] = atoi(argv[i]);
    print_int(val, argc - 2);
  }
  else if (strcmp(argv[1], "char") == 0) {
    char *val = (char *)malloc((argc - 2) * sizeof(char *));
    for (int i = 0; i < argc - 2; i++)
      val[i] = argv[i + 2][0];
    print_char(val, argc - 2);
    free(val);
  }
  else if (strcmp(argv[1], "str") == 0) {
    char **val = (char**)malloc((argc - 2) * sizeof(char*));
    my_memcpy(val, argv + 2, (argc - 2) * sizeof(char *));
    print_str(val, argc - 2);
    free(val);
  }
  return 0;
}
