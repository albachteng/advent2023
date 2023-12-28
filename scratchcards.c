#include "set.c"

function int set_summation(Set *s) {
  int total = 0;
  for (ptrdiff_t i = 0; i < s->size; i++) {
    total += s->elements[i];
  }
  return total;
}

int main() {
  int total = 0;
  line_reader *reader = new_line_reader("input4.txt", 1024);
  s8_parsed line = next_line(reader);
  while (line.ok) {
    char *winning_str = strsep(&line.str.data, ":");
    winning_str = strsep(&line.str.data, ":");
    char *matching_str = strsep(&winning_str, "|");
    Set matching_numbers;
    set_init(&matching_numbers);
    Set winning_numbers;
    set_init(&winning_numbers);
    ptrdiff_t count = 0;
    char *token, *rest = winning_str;
    while ((token = strsep(&rest, " ")) != NULL && count < 25) {
      if (*token != '\0') {
        printf("%td: %s \n", count, token);
        set_push(&matching_numbers, atoi(token));
        count++;
      }
    }
    token = rest = matching_str;
    count = 0;
    while ((token = strsep(&rest, " ")) != NULL && count < 10) {
      if (*token != '\0') {
        printf("%td: %s \n", count, token);
        // winning_numbers[count] = atoi(token);
        set_push(&winning_numbers, atoi(token));
        count++;
      }
    }
    set_print(&winning_numbers);
    set_print(&matching_numbers);
    Set *intersection = set_intersection(&winning_numbers, &matching_numbers);
    set_print(intersection);
    int points = 0;
    if (intersection->size > 0)
      points = 1;
    for (ptrdiff_t i = 0; i < intersection->size - 1; i++) {
      points *= 2;
    }
    // int sum = set_summation(intersection);
    printf("this line: size %td, points %d", intersection->size, points);
    total += points;
    line = next_line(reader);
  }
  printf("\ntotal: %d\n", total);
}
