#include "s8.h"
#include <stdio.h>

function b32 s8equals(s8 first, s8 second) {
  if (first.len != second.len) {
    return 0;
  }
  for (size i = 0; i < first.len; i++) {
    if (first.data[i] != second.data[i])
      return 0;
  }
  return 1;
};

function void s8copy(u8 *dst, byte *src, size sz) {
  u8 *originalDest = dst;
  while (sz > 0 && *src != '\0') {
    *dst = *src;
    dst++;
    src++;
    sz--;
  }
  while (sz > 0) {
    *dst = '\0';
    dst++;
    sz--;
  }
};

// function s8 s8prefix(s8 src, s8 dst){
//
// };

// returns the character from the string at poition pos
function byte_parsed s8at(s8 src, u32 pos) {
  byte_parsed out = (byte_parsed){.data = ' ', .ok = 0};
  if (src.len < pos || pos < 0) {
    return out;
  }
  out.data = src.data[pos];
  out.ok = 1;
  return out;
};
