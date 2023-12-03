#include "base_types.h"
#include <string.h>

typedef struct {
  char *beg;
  char *end;
} arena;

void *alloc(arena *a, size length, size align, size count);
