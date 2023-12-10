#include "base_types.h"
#include <string.h>

#define new(a, t, n) (t *)alloc(a, sizeof(t), _Alignof(t), n)

typedef struct {
  char *beg;
  char *end;
} arena;

void *alloc(arena *a, size length, size align, size count);
