#include "io.h"
#include <stddef.h>
#include <stdlib.h>

#define MAX_SET_SIZE 100

typedef struct {
  ptrdiff_t size;
  int *elements;
} Set;

function void set_init(Set *s) {
  s->elements = malloc(sizeof(int) * MAX_SET_SIZE);
  s->size = 0;
}

function b32 set_has(Set *s, int el) {
  for (ptrdiff_t i = 0; i < s->size; i++) {
    if (s->elements[i] == el)
      return 1;
  }
  return 0;
}

function void set_push(Set *s, int el) {
  if (s->size >= MAX_SET_SIZE) {
    fprintf(stderr, "set is full");
    exit(EXIT_FAILURE);
  }
  if (!set_has(s, el)) {
    s->elements[s->size] = el;
    s->size++;
    return;
  }
  // TODO: fails silently?
}

function Set *set_union(Set *first, Set *second) {
  Set *out = malloc(sizeof(Set));
  set_init(out);
  for (ptrdiff_t i = 0; i < first->size; i++) {
    set_push(out, first->elements[i]);
  }
  for (ptrdiff_t i = 0; i < second->size; i++) {
    set_push(out, second->elements[i]);
  }
  return out;
}

function Set *set_intersection(Set *first, Set *second) {
  Set *out = malloc(sizeof(Set));
  set_init(out);
  for (ptrdiff_t i = 0; i < first->size; i++) {
    if (set_has(second, first->elements[i])) {
      set_push(out, first->elements[i]);
    }
  }
  return out;
}

function void set_print(Set *s) {
  for (ptrdiff_t i = 0; i < s->size; i++) {
    printf("\ns->%td: %d", i, s->elements[i]);
  }
}
//
// int main(void) {
//   Set s1;
//   Set s2;
//   set_init(&s1);
//   set_init(&s2);
//
//   set_push(&s1, 1);
//   set_push(&s1, 2);
//   set_push(&s1, 3);
//   set_push(&s1, 4);
//   set_push(&s1, 5);
//
//   set_push(&s2, 3);
//   set_push(&s1, 6);
//   Set *s3 = set_intersection(&s1, &s2);
//   set_print(s3);
// }
