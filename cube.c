#include "io.c"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORDS 100
#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

function void toggle(b32 *bool) { *bool = (*bool != (b32)1) ? 1 : 0; }

function char **splitString(const char *str, ptrdiff_t *count);

int main(void) {
  int total = 0;
  int game_number = 1;
  line_reader *reader = new_line_reader("input2.txt", MAX_LINE_LENGTH);
  s8_parsed line = next_line(reader);
  // b32 is_possible = 1;
  while (line.ok) {
    printf("%s", line.str.data);
    ptrdiff_t wordcount = 0;
    char **words = splitString(line.str.data, &wordcount);
    b32 isColor = 1;
    int curr_num;
    int min_green = 0;
    int min_red = 0;
    int min_blue = 0;
    for (ptrdiff_t i = 0; i < wordcount; i++) {
      toggle(&isColor);
      if (isColor) {
        if (words[i][0] == 'g' /*&& curr_num > GREEN_MAX*/) {
          min_green = (curr_num > min_green) ? curr_num : min_green;
          curr_num = 0;
          // is_possible = 0;
          // break;
        }
        if (words[i][0] == 'r' /*&& curr_num > RED_MAX*/) {
          min_red = (curr_num > min_red) ? curr_num : min_red;
          curr_num = 0;
          // is_possible = 0;
          // break;
        }

        if (words[i][0] == 'b' /*&& curr_num > BLUE_MAX*/) {
          min_blue = (curr_num > min_blue) ? curr_num : min_blue;
          curr_num = 0;
          // is_possible = 0;
          // break;
        }
      } else {
        curr_num = atoi(words[i]);
      }
    }
    // if (is_possible) {
    //   printf("game # %d is valid", game_number);
    total += (min_green * min_red * min_blue);
    printf("total = %d", total);
    // }
    game_number++;
    printf("RGB = min_red %d\t min_blue %d\t min_green %d\n", min_red, min_blue,
           min_green);
    min_green = min_blue = min_red = 0;
    // is_possible = 1;
    line = next_line(reader);
  }
  printf("total = %d", total);
}

function char **splitString(const char *str, ptrdiff_t *count) {
  char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
  if (words == NULL) {
    fprintf(stderr, "failed allocation in splitString");
    exit(EXIT_FAILURE);
  }
  char *token = strtok((char *)str, " ");
  if (count == NULL)
    printf("WHY?");
  *count = 0;
  while (token != NULL) {
    words[*count] = (char *)malloc(strlen(token) + 1);
    if (words[*count] == NULL) {
      fprintf(stderr, "allocation failed while tokenizing");
      exit(EXIT_FAILURE);
    }
    strcpy(words[*count], token);
    token = strtok(NULL, " ");
    (*count)++;
    if (*count >= MAX_WORDS) {
      fprintf(stderr, "overflow MAX_WORDS");
      exit(EXIT_FAILURE);
    }
  }
  return words;
}
