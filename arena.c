#include "arena.h"
#include "base.h"
#include "base_types.h"
#include <assert.h>

void *alloc(arena *a, size length, size align, size count) {
  size avail = a->end - a->beg;
  size padding = -(usize)a->beg & (align - 1);
  if (count > (avail - padding) / length) {
    assert(0); // TODO
  }
  size total = length * count;
  char *p = a->beg + padding;
  a->beg += padding + total;
  return memset(p, 0, total); // TODO
}
