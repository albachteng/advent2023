#include <stddef.h>
#include <string.h>

#define new(a, t, n) (t *)alloc(a, sizeof(t), _Alignof(t), n)

typedef struct {
  char *beg;
  char *end;
} arena;

void *alloc(arena *a, ptrdiff_t length, ptrdiff_t align, ptrdiff_t count);
arena init_arena();
