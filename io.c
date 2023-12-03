#include "io.h"
#include <stdio.h>

function FILE *open(const byte *name) {
  FILE *file = fopen(name, "r");
  if (file == NULL) {
    assert(0);
    return NULL;
  }
  return file;
};

s8_parsed nextline(FILE *file) {
  static byte line[MAX_LINE_LENGTH];
  if (fgets(line, sizeof(line), file) != NULL) {
    return (s8_parsed){.str = s8(line), .ok = 1};
  }
  return (s8_parsed){.str = s8("EOF"), .ok = 0};
};

int main() {
  FILE *file = open("nonsense.txt");
  s8_parsed line;
  line = nextline(file);
  while (line.ok) {
    printf("%s", line.str.data);
    line = nextline(file);
  }
  printf("%s", line.str.data);
}
