#include <stdlib.h>

void *my_memcpy(void *orig_dest, const void *orig_src, size_t quantity) {
  char *cur_dest = (char*)orig_dest;
  const char *cur_src = (char*)orig_src;
  for (size_t i = 0; i < quantity; i++)
    *cur_dest++ = *cur_src++;
  return orig_dest;
}
