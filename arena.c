#include "arena.h"
#include "base.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define ARENA_SIZE 1024

arena init_arena() {
  arena ar;
  ar.beg = (char *)malloc(ARENA_SIZE);
  ar.end = ar.beg + ARENA_SIZE;
  return ar;
};

void *alloc(arena *a, ptrdiff_t length, ptrdiff_t align, ptrdiff_t count) {
  ptrdiff_t avail = a->end - a->beg;
  ptrdiff_t padding = -(size_t)a->beg & (align - 1);
  if (count > (avail - padding) / length) {
    assert(0); // TODO
  }
  ptrdiff_t total = length * count;
  char *p = a->beg + padding;
  a->beg += padding + total;
  return memset(p, 0, total); // TODO
}
