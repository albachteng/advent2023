#include "arena.h"
#include "base.h"
#include <assert.h>
#include <stddef.h>

arena arena_init(char *start, ptrdiff_t size) {
  arena ar;
  ar.beg = start;
  ar.end = start + size;
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
