#include "base.h"
#include "base_types.h"

// wraps a c string literal and makes an s8 out of it
#define s8(s)                                                                  \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  u8 *data;
  size len;
} s8; // UTF-8 strings

function b32 s8equals(s8 first, s8 second);
// function s8 s8clone(u8 *src, u8 *dst);
// function s8 s8prefix(s8 src, s8 dst);
