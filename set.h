#include "base.h"
#include "io.c"
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  ptrdiff_t size;
  int *elements;
} Set;

function void set_init(Set *s);
function b32 set_has(Set *s, int el);
function void set_push(Set *s, int el);
function Set *set_union(Set *first, Set *second);
function Set *set_intersection(Set *first, Set *second);
function void set_print(Set *s);
