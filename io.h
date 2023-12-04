#include "base.h"
#include "s8.c"
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
  FILE *file;
  byte *line_buffer;
  size line_buffer_size;
  s8 current_line;
} LineReader;

function FILE *open(const char *);
s8_parsed nextline(FILE *file);
