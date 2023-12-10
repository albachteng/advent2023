#include "s8.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

function void s8_print(s8 str) {
  for (ptrdiff_t i = 0; i < str.len; i++) {
    putchar(str.data[i]);
  }
  putchar('\n');
}

function b32 s8equals(s8 first, s8 second) {
  if (first.len != second.len) {
    return 0;
  }
  for (ptrdiff_t i = 0; i < first.len; i++) {
    if (first.data[i] != second.data[i])
      return 0;
  }
  return 1;
};

function s8 s8clone(s8 src) {
  s8 dst;
  dst.data = (char *)malloc(src.len + 1);
  if (dst.data == NULL) {
    printf("error in malloc for s8copy");
    exit(1);
  }
  strncpy(dst.data, src.data, src.len);
  dst.data[src.len] = '\0';
  dst.len = src.len;
  s8_print(dst);
  return dst;
};

// function s8 s8prefix(s8 src, char ch){
//
// };

function s8 s8postfix(s8 src, char ch) {
  s8 result;
  result.data = (char *)malloc(
      src.len + 2); // +2 for the new character and null terminator
  if (result.data == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  strncpy(result.data, src.data, src.len);
  result.data[src.len] = ch;
  result.data[src.len + 1] = '\0';
  result.len = src.len + 1;
  return result;
};

int main() {
  s8 src = s8("hi");
  printf("%s\n", src.data);
  s8_print(src);
  char ch = '!';
  s8 cpy = s8clone(src);
  s8_print(cpy);
  printf("%s\n", cpy.data);
  printf("len = %td\n", cpy.len);
  s8 new = s8postfix(src, ch);
  s8_print(cpy);
  printf("len = %td\n", cpy.len);
  s8_print(new);
  printf("len = %td\n", new.len);
}

// returns the character from the string at poition pos
function char_parsed s8at(s8 src, int pos) {
  char_parsed out = (char_parsed){.data = ' ', .ok = 0};
  if (src.len < pos || pos < 0) {
    return out;
  }
  out.data = src.data[pos];
  out.ok = 1;
  return out;
};
