#include "base.h"
#include "s8.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
  s8 str;
  b32 ok;
} s8_parsed;

function FILE *open(const char *);
s8_parsed nextline(FILE *file);
