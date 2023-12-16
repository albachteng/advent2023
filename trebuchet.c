#include "base.h"
#include "io.c"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

b32 char_is_num(char);
int make_two_digit(char_parsed, char_parsed);
function char_parsed str_to_byte(char *str);
function char *get_substr(char *str, ptrdiff_t beg, ptrdiff_t end);

global char *lookup[] = {"zero", "one", "two",   "three", "four",
                         "five", "six", "seven", "eight", "nine"};

int main() {
  int total = 0;
  line_reader *reader = new_line_reader("input.txt", 1024);
  s8_parsed line = next_line(reader);

  while (line.ok) {
    char_parsed first_digit = (char_parsed){0};
    char_parsed second_digit = (char_parsed){0};
    ptrdiff_t start = 0;
    for (ptrdiff_t end = 0; end < line.str.len - 1; end++) {
      if (line.str.data[end]) {
        // char was num
        if (char_is_num(line.str.data[end])) {
          printf("shouldn't be hitting this\n");
          // reset start
          start = end + 1;
          if (!first_digit.ok) {
            first_digit = (char_parsed){line.str.data[end], 1};
          } else {
            second_digit = (char_parsed){line.str.data[end], 1};
          }
        } else {
          // char was not num
          // get substr from start to end
          for (ptrdiff_t i = start; i < end; i++) {
            char *substr = get_substr(line.str.data, i, end);
            printf("line = %s\n", line.str.data);
            printf("substr = %s\n", substr);
            // check against lookup table
            char_parsed strch = str_to_byte(substr);
            printf("strch = %c\n", strch.data);
            // if we find a word, add its number to first or second digit as
            // appropriate then reset start = end to get ready for next word
            if (strch.ok) {
              printf("strch was ok\n");
              // if we found a word, set start to after the word we found
              start = i + strlen(substr) - 1; // NTS might be off by 1
              // also set i, no need to check inside a word
              i = start;
              if (!first_digit.ok) {
                first_digit.data = strch.data;
                first_digit.ok = 1;
              } else {
                second_digit.data = strch.data;
                second_digit.ok = 1;
              }
              // start = end + 1; NTS not sure if this is still necessary
            }
          }
          printf("start = %td end = %td\n", start, end);
        }
      }
    }
    int to_add = make_two_digit(first_digit, second_digit);
    printf("to add: %d\n", to_add);
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

function char *get_substr(char *str, ptrdiff_t beg, ptrdiff_t end) {
  ptrdiff_t len = strlen(str);
  if (beg > end || beg >= len) {
    return NULL;
  }
  end = (end >= len) ? len - 1 : end;
  ptrdiff_t substr_len = end - beg + 1;
  char *substr = (char *)malloc(sizeof(char) * substr_len);
  if (substr == NULL) {
    fprintf(stderr, "malloc failed in get_substr");
    exit(EXIT_FAILURE);
  }
  strncpy(substr, str + beg, substr_len);
  substr[substr_len] = '\0';
  return substr;
}

int make_two_digit(char_parsed first, char_parsed second) {
  int tens;
  int ones;
  printf("first = %c, second = %c\n", first.data, second.data);
  tens = first.data - '0';
  if (second.ok && char_is_num(second.data)) {
    ones = second.data - '0';
  } else {
    ones = tens;
  }
  printf("tens = %d, ones = %d\n", tens, ones);
  return (tens * 10) + ones;
}

function char_parsed str_to_byte(char *str) {
  printf("str = %s\n", str);
  for (ptrdiff_t i = 0; i < 10; i++) {
    if (!strcmp(str, lookup[i])) {
      printf("strcmp successful with %s\n", lookup[i]);
      char ch = i + '0';
      return (char_parsed){.data = ch, .ok = 1};
    }
  }
  return (char_parsed){' ', 0};
}
