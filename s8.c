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

int main() {
  s8 first = s8("hello");
  s8 second = s8("hello");
  printf("is equal: %d", s8equals(first, second));
}
// function s8 s8clone(u8 *src, u8 *dst){
//
// };

// function s8 s8prefix(s8 src, s8 dst){
//
// };
