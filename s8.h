#include "arena.h"
#include "base.h"
#include <stddef.h>

// wraps a c string literal and makes an s8 out of it
#define s8(s)                                                                  \
  (s8) { (char *)s, lengthof(s) }

typedef int b32;

typedef struct {
  char *data;
  ptrdiff_t len;
} s8; // UTF-8 strings

typedef struct s8node {
  struct s8node *next;
  s8 val;
} s8node;

typedef struct {
  s8node *head;
  s8node *tail;
  arena arena;
} s8list;

typedef struct {
  char data;
  b32 ok;
} char_parsed;

typedef struct {
  s8 str;
  b32 ok;
} s8_parsed;
