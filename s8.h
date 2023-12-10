#include "base.h"
#include "base_types.h"

// wraps a c string literal and makes an s8 out of it
#define s8(s)                                                                  \
  (s8) { (byte *)s, lengthof(s) }

typedef struct {
  byte *data;
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
