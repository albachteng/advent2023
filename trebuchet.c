#include "base.h"
#include "base_types.h"
#include "io.c"
#include <assert.h>

b32 char_is_num(byte);
u32 make_two_digit(byte_parsed, byte_parsed);

i32 main() {
  u32 total = 0;
  LineReader *reader = createLineReader("input.txt", 1024);
  s8 line = readNextLine(reader);
  // FILE *file = open("input.txt");
  // s8_parsed line = nextline(file);

  while (line.len) {
    byte_parsed first_digit = (byte_parsed){0};
    byte_parsed second_digit = (byte_parsed){0};
    assert(!second_digit.ok);
    assert(!first_digit.ok);

    for (size i = 0; i < line.len; i++) {
      byte_parsed ch = s8at(line, i);
      if (ch.ok && char_is_num(ch.data)) {
        if (!first_digit.ok) {
          first_digit = ch;
        } else {
          second_digit = ch;
        }
      }
    }
    u32 to_add;
    printf("line: %s \n", line.data);
    printf("first: %d, second: %d \n", first_digit.data - '0',
           second_digit.data - '0');
    to_add = make_two_digit(first_digit, second_digit);
    printf("to_add: %d\n", to_add);
    total += to_add;
    line = readNextLine(reader);
  }
  printf("total = %d\n", total);
  return 1;
};

b32 char_is_num(byte ch) {
  if (ch >= '0' && ch <= '9') {
    printf("num is: %d\n", ch - '0');
    return 1;
  }
  return 0;
}

u32 make_two_digit(byte_parsed first, byte_parsed second) {
  u32 tens;
  u32 ones;
  tens = first.data - '0';
  if (second.ok && char_is_num(second.data)) {
    printf("second was OK = %d\n", second.data - '0');
    ones = second.data - '0';
  } else {
    ones = tens;
  }
  return (tens * 10) + ones;
}
