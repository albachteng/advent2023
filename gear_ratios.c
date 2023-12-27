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
  int line_number = 2;
  line_reader *reader = new_line_reader("input3.txt", MAX_LINE_LENGTH);
  // s8_parsed prev_line = next_line(reader);
  s8_parsed curr_line = next_line(reader);
  s8 *prev_line;
  prev_line->data = malloc(sizeof(char) * curr_line.str.len);
  strncpy(prev_line->data, curr_line.str.data, curr_line.str.len);
  prev_line->len = curr_line.str.len;
  curr_line = next_line(reader);
  ptrdiff_t prev_symb_count = 0;
  ptrdiff_t curr_symb_count = 0;
  ptrdiff_t *prev_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);
  ptrdiff_t *curr_symb_arr = malloc(sizeof(ptrdiff_t) * MAX_LINE_LENGTH);

  while (line_number <= 141) {
    b32 same = strcmp(prev_line->data, curr_line.str.data);
    printf("same? %d", same);
    printf("line number: %d\n", line_number);
    printf("prev line = %s\n", prev_line->data);
    printf("curr line = %s\n", curr_line.str.data);
    for (ptrdiff_t i = 0; i < curr_line.str.len; i++) {
      if (char_is_symbol(curr_line.str.data[i])) {
        // printf("%c @ %td is symbol\n", curr_line.str.data[i], i);
        add_pos(curr_symb_arr, i, curr_symb_count);
        curr_symb_count++;
        // printf("curr_symb_arr = ");
        // for (ptrdiff_t i = 0; i < curr_symb_count; i++) {
        //   printf("%td ", curr_symb_arr[i]);
        // }
        // printf("\n");
        // printf("curr_symb_count = %td\n", curr_symb_count);
      }
    }
    // note that first line always has zero symbols
    // prev_line symbols -> curr_line
    printf("prev line symbols v. curr line: \n");
    for (ptrdiff_t prev_symb_idx = 0; prev_symb_idx < prev_symb_count;
         prev_symb_idx++) {
      printf("prev symb indx: prev symb arr @ prev symb indx\n");
      printf("#%td: %td ", prev_symb_idx, prev_symb_arr[prev_symb_idx]);
      ptrdiff_t curr_idx = prev_symb_arr[prev_symb_idx];
      printf("\n");
      if (char_is_num(curr_line.str.data[curr_idx - 1])) {
        // step back until not a number - no need to do this for the next two
        printf("found %c, stepping back\n", curr_line.str.data[curr_idx - 1]);
        ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx - 1);
        printf("temp_idx = %td\n", temp_idx);
        // add number to total
        int to_add = add_to_total(curr_line.str.data, temp_idx);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        // zero out the number
        printf("zeroing out\n");
        zero_out(curr_line.str.data, temp_idx);
        printf("after zeroing: %s\n", curr_line.str.data);
      }
      if (char_is_num(curr_line.str.data[curr_idx])) {
        printf("found %c\n", curr_line.str.data[curr_idx]);
        // ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx);
        // NTS - no reason to step back here?
        int to_add = add_to_total(curr_line.str.data, curr_idx);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(curr_line.str.data, curr_idx);
        printf("after zeroing: %s\n", curr_line.str.data);
      }
      if (char_is_num(curr_line.str.data[curr_idx + 1])) {
        printf("found %c\n", curr_line.str.data[curr_idx + 1]);
        int to_add = add_to_total(curr_line.str.data, curr_idx + 1);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(curr_line.str.data, curr_idx + 1);
        printf("after zeroing: %s\n", curr_line.str.data);
      }
    }
    // curr_line symbols -> prev_line
    printf("curr line symbols v prev line\n");
    for (ptrdiff_t curr_symb_idx = 0; curr_symb_idx < curr_symb_count;
         curr_symb_idx++) {
      printf("curr symb indx: prev symb arr @ curr symb indx\n");
      printf("#%td: %td ", curr_symb_idx, prev_symb_arr[curr_symb_idx]);
      ptrdiff_t curr_idx = curr_symb_arr[curr_symb_idx];
      if (char_is_num(prev_line->data[curr_idx - 1])) {
        printf("found %c @ %td\n", prev_line->data[curr_idx - 1], curr_idx - 1);
        printf("stepping back\n");
        ptrdiff_t temp_idx = step_back(prev_line->data, curr_idx - 1);
        printf("temp indx = %td\n", temp_idx);
        int to_add = add_to_total(prev_line->data, temp_idx);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(prev_line->data, temp_idx); // NTS: need to be a pointer???
        printf("after zeroing: %s\n", prev_line->data);
      }
      if (char_is_num(prev_line->data[curr_idx])) {
        printf("found %c @ %td\n", prev_line->data[curr_idx], curr_idx);
        int to_add = add_to_total(prev_line->data, curr_idx);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(prev_line->data, curr_idx);
        printf("after zeroing: %s\n", prev_line->data);
      }
      if (char_is_num(prev_line->data[curr_idx + 1])) {
        printf("found %c @ %td\n", prev_line->data[curr_idx + 1], curr_idx + 1);
        int to_add = add_to_total(prev_line->data, curr_idx + 1);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(prev_line->data, curr_idx + 1);
        printf("after zeroing: %s\n", prev_line->data);
      }
      // curr_line symbols -> curr_line
      printf("curr line symb v. curr line\n");
      if (char_is_num(curr_line.str.data[curr_idx - 1])) {
        printf("found %c @ %td\n", curr_line.str.data[curr_idx - 1],
               curr_idx - 1);
        ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx - 1);
        printf("temp idx = %td \n", temp_idx);
        int to_add = add_to_total(curr_line.str.data, temp_idx);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(curr_line.str.data, temp_idx);
        printf("after zeroing: %s\n", curr_line.str.data);
      }
      if (char_is_num(curr_line.str.data[curr_idx + 1])) {
        printf("found %c @ %td\n", curr_line.str.data[curr_idx + 1],
               curr_idx + 1);
        // ptrdiff_t temp_idx = step_back(curr_line.str.data, curr_idx + 1);
        // NTS no reason to step back?
        printf("char = %c", curr_line.str.data[curr_idx + 1]);
        int to_add = add_to_total(curr_line.str.data, curr_idx + 1);
        total += to_add;
        printf("adding %d to total, total is now %d\n", to_add, total);
        printf("zeroing out\n");
        zero_out(curr_line.str.data, curr_idx + 1);
        printf("after zeroing: %s\n", curr_line.str.data);
      }
    }
    printf("out of inner loop\n");
    printf("\ntotal = %d", total);
    printf("\n");
    printf("\n prev line: %s\n", prev_line->data);
    strncpy(prev_line->data, curr_line.str.data, curr_line.str.len);
    curr_line = next_line(reader);
    prev_symb_count = curr_symb_count;
    prev_symb_arr = curr_symb_arr;
    curr_symb_count = 0;
    line_number++;
  }
  printf("out of outer loop\n");
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
  return atoi(&line[start]);
}

function void zero_out(char *line, ptrdiff_t start) {
  int end = start;
  while (char_is_num(line[end + 1])) {
    end++;
  }
  for (ptrdiff_t i = start; i <= end; i++) {
    line[i] = '0';
  }
}
