#include "io.c"
#include <stddef.h>

function b32 char_is_num(char ch) { return (ch >= '0' && ch <= '9') ? 1 : 0; }

function b32 is_symbol(char ch) {
  return (!char_is_num(ch) && ch != '.' && ch != '\n') ? 1 : 0;
}
function void toggle(b32 *bool) { *bool = (*bool) ? 0 : 1; }
function void on(b32 *bool) { *bool = 1; }
function void off(b32 *bool) { *bool = 0; }
function void add_pos(ptrdiff_t *positions, ptrdiff_t pos, ptrdiff_t count) {
  positions[count] = pos;
};

int main(void) {
  int total = 0;
  int line_number = 1;
  line_reader *reader = new_line_reader("input3.txt", MAX_LINE_LENGTH);
  s8_parsed curr_line = next_line(reader);
  s8_parsed prev_line;
  ptrdiff_t curr_num_count = 0;
  ptrdiff_t curr_symb_count = 0;
  ptrdiff_t prev_num_count = 0;
  ptrdiff_t prev_symb_count = 0;
  ptrdiff_t *curr_num_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);
  ptrdiff_t *curr_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);
  ptrdiff_t *prev_num_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);
  ptrdiff_t *prev_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);

  while (curr_line.ok) {
    printf("%s\n", curr_line.str.data);
    for (ptrdiff_t i = 0; i < curr_line.str.len; i++) {
      if (char_is_num(curr_line.str.data[i])) {
        // add start pos of number
        add_pos(curr_num_arr, i, curr_num_count);
        curr_num_count++;
        // if (is_number(curr_line.str.data[i + 1]))
        //   i++;
        // continue until we hit the end of the number
        while (char_is_num(curr_line.str.data[i + 1])) {
          i++;
        }

        // add end of num position
        // two of the same number indicates single digit
        add_pos(curr_num_arr, i, curr_num_count);
        curr_num_count++;
      } else if (is_symbol(curr_line.str.data[i])) {
        add_pos(curr_symb_arr, i, curr_symb_count);
        curr_symb_count++;
      }
    }
    printf("numbers: (");
    for (ptrdiff_t j = 0; j < curr_num_count; j++) {
      printf("%td, ", curr_num_arr[j]);
    }
    printf(") \n");
    printf("symbols: ");
    for (ptrdiff_t k = 0; k < curr_symb_count; k++) {
      printf("%td ", curr_symb_arr[k]);
    }
    printf("\n");
    printf("\n prev line: %s\n", prev_line.str.data);
    prev_line = curr_line;
    curr_line = next_line(reader);
    prev_num_arr = curr_num_arr;
    curr_num_count = 0;
    curr_symb_count = 0;
  }
  // for every two lines
  // if you hit a number:
  // if in a symbol is true, we need to add this number and flip in_symbol
  // if not already in a number, record starting position of number
  // flip "in a number" to true
  // else if in any non-period symbol
  // if in a number, flip to off and record ending position of number
  // in this case, the number we just flipped off is valid, add to total
  // compare position of symbol to number positions in previous line
  // if any are adjacent and not already added, add that number to the total
  // if we don't already know this was adjacent to a number, there are two
  // remaining cases: 1) the symbol is not adjacent to any numbers, we do
  // nothing 2) there is a number directly in front of it that must be added
  // so we have a switch for "in a symbol" which we turn to on and add check
  // above
  // else (if you hit a period):
  // if in a number, flip to off and record ending position of number
  free(curr_num_arr);
  free(curr_symb_arr);
}
