#include "base.h"
#include "s8.c"
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
  FILE *file;
  s8 line_buffer;
  s8 current_line;
} line_reader;
