#include "base.h"
#include "base_types.h"
#include "io.c"
#include <assert.h>

b32 char_is_num(byte);
u32 make_two_digit(byte_parsed, byte_parsed);

i32 main() {
  u32 total = 0;
  line_reader *reader = new_line_reader("input.txt", 1024);
  s8_parsed line = next_line(reader);

  while (line.ok) {
    byte_parsed first_digit = (byte_parsed){0};
    byte_parsed second_digit = (byte_parsed){0};

    for (size i = 0; i < line.str.len; i++) {
      byte_parsed ch = s8at(line.str, i);
      if (ch.ok && char_is_num(ch.data)) {
        if (!first_digit.ok) {
          first_digit = ch;
        } else {
          second_digit = ch;
        }
      }
    }
    u32 to_add = make_two_digit(first_digit, second_digit);
    total += to_add;
    line = next_line(reader);
  }
  printf("total = %d\n", total);
  return 1;
};

b32 char_is_num(byte ch) {
  if (ch >= '0' && ch <= '9') {
    return 1;
  }
  return 0;
}

u32 make_two_digit(byte_parsed first, byte_parsed second) {
  u32 tens;
  u32 ones;
  tens = first.data - '0';
  if (second.ok && char_is_num(second.data)) {
    ones = second.data - '0';
  } else {
    ones = tens;
  }
  return (tens * 10) + ones;
}
