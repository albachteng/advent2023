#include "io.c"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

function void zero_out(char *line, ptrdiff_t start);
function ptrdiff_t step_back(char *line, ptrdiff_t curr_idx);
function int add_to_total(char *line, ptrdiff_t start);
function b32 char_is_num(char ch) { return (ch >= '0' && ch <= '9') ? 1 : 0; }

function b32 char_is_symbol(char ch) {
  return (!char_is_num(ch) && ch != '.' && ch != '\n') ? 1 : 0;
}
function void add_pos(ptrdiff_t *positions, ptrdiff_t pos, ptrdiff_t count) {
  positions[count] = pos;
};

int main() {
  int total = 0;
  int line_number = 1;
  line_reader *reader = new_line_reader("input3.txt", MAX_LINE_LENGTH);
  s8_parsed prev_line = next_line(reader);
  s8_parsed curr_line = next_line(reader);
  ptrdiff_t prev_symb_count = 0;
  ptrdiff_t curr_symb_count = 0;
  ptrdiff_t *prev_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);
  ptrdiff_t *curr_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);

  while (curr_line.ok) {
    printf("%s\n", curr_line.str.data);
    for (ptrdiff_t i = 0; i < curr_line.str.len; i++) {
      if (char_is_symbol(curr_line.str.data[i])) {
        add_pos(curr_symb_arr, i, curr_symb_count);
        curr_symb_count++;
      }
    }
    // note that first line always has zero symbols
    // prev_line symbols -> curr_line
    printf("symbols: ");
    for (ptrdiff_t prev_symb_idx = 0; prev_symb_idx < prev_symb_count;
         prev_symb_idx++) {
      printf("%td ", prev_symb_arr[prev_symb_idx]);
      ptrdiff_t curr_idx = prev_symb_arr[prev_symb_idx];
      if (char_is_num(prev_line.str.data[curr_idx - 1])) {
        // step back until not a number - no need to do this for the next two
        ptrdiff_t temp_idx = step_back(prev_line.str.data, curr_idx - 1);
        // add number to total
        total += add_to_total(prev_line.str.data, temp_idx);
        // zero out the number
        zero_out(prev_line.str.data, temp_idx);
      }
      if (char_is_num(prev_line.str.data[curr_idx])) {
        ptrdiff_t temp_idx = step_back(prev_line.str.data, curr_idx);
        total += add_to_total(prev_line.str.data, temp_idx);
        zero_out(prev_line.str.data, temp_idx);
      }
      if (char_is_num(prev_line.str.data[curr_idx + 1])) {
        total += add_to_total(prev_line.str.data, curr_idx + 1);
        zero_out(prev_line.str.data, curr_idx + 1);
      }
    }
    // curr_line symbols -> prev_line
    for (ptrdiff_t curr_symb_idx = 0; curr_symb_idx < curr_symb_count;
         curr_symb_idx++) {
      ptrdiff_t curr_idx = curr_symb_arr[curr_symb_idx];
      if (char_is_num(prev_line.str.data[curr_idx - 1])) {
        printf("1");
        ptrdiff_t temp_idx = step_back(prev_line.str.data, curr_idx - 1);
        total += add_to_total(prev_line.str.data, temp_idx);
        zero_out(prev_line.str.data, temp_idx);
      }
      if (char_is_num(prev_line.str.data[curr_idx])) {
        printf("2");
        total += add_to_total(prev_line.str.data, curr_idx);
        zero_out(prev_line.str.data, curr_idx);
      }
      if (char_is_num(prev_line.str.data[curr_idx + 1])) {
        printf("3");
        total += add_to_total(prev_line.str.data, curr_idx + 1);
        zero_out(prev_line.str.data, curr_idx);
      }
      // curr_line symbols -> curr_line
      if (char_is_num(curr_line.str.data[curr_idx - 1])) {
        printf("4");
        ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx - 1);
        total += add_to_total(curr_line.str.data, temp_idx);
        zero_out(curr_line.str.data, temp_idx);
      }
      if (char_is_num(curr_line.str.data[curr_idx + 1])) {
        printf("5");
        ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx + 1);
        printf("\ntemp inx: %td\n", temp_idx);
        printf("char = %c", curr_line.str.data[temp_idx]);
        total += add_to_total(curr_line.str.data, temp_idx);
        zero_out(curr_line.str.data, temp_idx);
      }
    }
    printf("\ntotal = %d", total);
    printf("\n");
    printf("\n prev line: %s\n", prev_line.str.data);
    prev_line = curr_line;
    curr_line = next_line(reader);
    curr_symb_count = 0;
  }
  printf("\ntotal = %d", total);
  free(curr_symb_arr);
}

function ptrdiff_t step_back(char *line, ptrdiff_t curr_idx) {
  while (char_is_num(line[curr_idx]) && curr_idx > 0) {
    curr_idx--;
  }
  return curr_idx + 1;
}

function int add_to_total(char *line, ptrdiff_t start) {
  int total = 0;
  int end = start;
  while (char_is_num(line[end + 1])) {
    end++;
  }
  int power = end - start;
  if (power < 0) { // something has gone wrong
    printf("power was less than zero");
    exit(EXIT_FAILURE);
  }
  for (ptrdiff_t i = start; i < end; i++) {
    if (!char_is_num(line[i])) {
      printf("char was not num - %c /t index %td\n", line[i],
             start); // something has gone wrong
      exit(EXIT_FAILURE);
    }
    total += (int)(pow(10, power) * atoi(&line[i]));
  }
  printf("total was: %d\n", total);
  return total;
}

function void zero_out(char *line, ptrdiff_t start) {
  int end = start;
  while (char_is_num(line[end + 1])) {
    end++;
  }
  for (ptrdiff_t i = start; i < end; i++) {
    line[i] = '0';
  }
}
