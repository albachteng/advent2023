#include "base.h"
#include "io.c"
#include <assert.h>
#include <stddef.h>

b32 char_is_num(char);
int make_two_digit(char_parsed, char_parsed);
function char_parsed str_to_byte(s8 str);

global char *lookup[] = {"zero", "one", "two",   "three", "four",
                         "five", "six", "seven", "eight", "nine"};

int main() {
  int total = 0;
  line_reader *reader = new_line_reader("input.txt", 1024);
  s8_parsed line = next_line(reader);

  while (line.ok) {
    char_parsed first_digit = (char_parsed){0};
    char_parsed second_digit = (char_parsed){0};
    s8 buf = (s8){0};
    for (ptrdiff_t i = 0; i < line.str.len; i++) {
      char_parsed ch = s8at(line.str, i);
      if (ch.ok) {
        // char was num
        if (char_is_num(ch.data)) {
          // reset buffer
          buf = (s8){0};
          if (!first_digit.ok) {
            first_digit = ch;
          } else {
            second_digit = ch;
          }
        } else {
          // char was not num, add next char and check against lookup table
          buf = s8postfix(buf, ch.data);
          char_parsed strch = str_to_byte(buf);
          if (strch.ok) {
            // reset buf
            buf = (s8){0};
            if (!first_digit.ok) {
              first_digit = strch;
            } else {
              second_digit = strch;
            }
          }
        }
      }
    }
    int to_add = make_two_digit(first_digit, second_digit);
    total += to_add;
    line = next_line(reader);
  }
  printf("total = %d\n", total);
  return 1;
};

b32 char_is_num(char ch) {
  if (ch >= '0' && ch <= '9') {
    return 1;
  }
  return 0;
}

int make_two_digit(char_parsed first, char_parsed second) {
  int tens;
  int ones;
  tens = first.data - '0';
  if (second.ok && char_is_num(second.data)) {
    ones = second.data - '0';
  } else {
    ones = tens;
  }
  return (tens * 10) + ones;
}

function char_parsed str_to_byte(s8 str) {
  // printf("str was: %s\n", str.data);
  for (ptrdiff_t i = 0; i < countof(lookup); i++) {
    if (s8equals(str, s8(lookup[i]))) {
      char ch = i + '0';
      // printf("byte was: %hhd\n", ch);
      return (char_parsed){.data = ch, .ok = 1};
    }
  }
  return (char_parsed){0};
}
