#include "base.h"
#include "base_types.h"

// wraps a c string literal and makes an s8 out of it
#define s8(s)                                                                  \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  u8 *data;
  size len;
} s8; // UTF-8 strings

typedef struct {
  byte data;
  b32 ok;
} byte_parsed;

typedef struct {
  s8 str;
  b32 ok;
} s8_parsed;

function b32 s8equals(s8 first, s8 second);
// function s8 s8clone(u8 *src, u8 *dst);
// function s8 s8prefix(s8 src, s8 dst);
function byte_parsed s8at(s8 src, u32 pos);
function void s8copy(u8 *src, byte *dst, size sz);
