#include <stdlib.h>
#include <string.h>

#include "mergesort.h"
#include "my_memcpy.h"

void merge(void *result, void *left, size_t left_len, void *right, size_t right_len, size_t element_size, int (*comparator)(const void *, const void *)) {
  size_t left_idx = 0, right_idx = 0;
  size_t elements = left_len + right_len;
  void *tmp_arr = malloc(elements * element_size);
  for (size_t i = 0; i < elements; i++) {
    if (left_idx < left_len && (right_idx >= right_len || comparator((char *)left + element_size * left_idx, (char *)right + element_size * right_idx) < 0)) {
      my_memcpy((char *)tmp_arr + i * element_size, (char *)left + element_size * left_idx, element_size);
      left_idx++;
    }
    else {
      my_memcpy((char *)tmp_arr + i * element_size, (char *)right + element_size * right_idx, element_size);
      right_idx++;
    }
  }
  my_memcpy(result, tmp_arr, elements * element_size);
  free(tmp_arr);
}

void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)){
  if (elements <= 1)
    return;
  size_t elem_half = elements / 2;
  mergesort(array, elem_half, element_size, comparator);
  mergesort((char *)array + elem_half * element_size, elements - elem_half, element_size, comparator);
  merge(array, array, elem_half, (char *)array + element_size * elem_half, elements - elem_half, element_size, comparator);
}
