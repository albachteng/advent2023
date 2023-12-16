#include "io.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

function FILE *open(const char *name) {
  FILE *file = fopen(name, "r");
  if (file == NULL) {
    assert(0);
    return NULL;
  }
  return file;
};

line_reader *new_line_reader(const char *filename, size_t line_buffer_size) {
  line_reader *reader = malloc(sizeof(line_reader));
  if (reader == NULL) {
    perror("Error creating LineReader");
    exit(EXIT_FAILURE);
  }

  reader->file = fopen(filename, "r");
  if (reader->file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  reader->line_buffer =
      (s8){.data = malloc(line_buffer_size), .len = line_buffer_size};
  if (reader->line_buffer.data == NULL) {
    perror("Error creating line buffer");
    exit(EXIT_FAILURE);
  }

  reader->line_buffer.len = line_buffer_size;
  reader->current_line = (s8){0};

  return reader;
}

s8_parsed next_line(line_reader *reader) {
  if (fgets((char *)reader->line_buffer.data, (int)reader->line_buffer.len,
            reader->file) == NULL) {
    return (s8_parsed){.str = s8("EOF"), .ok = 0};
  }

  ptrdiff_t bytesRead = strlen(reader->line_buffer.data);

  reader->current_line.data = realloc(reader->current_line.data, bytesRead);
  if (reader->current_line.data == NULL) {
    perror("Error allocating memory for line");
    exit(EXIT_FAILURE);
  }

  // Copy the line from the buffer to the allocated memory
  strncpy(reader->current_line.data, (char *)reader->line_buffer.data,
          bytesRead); // TODO
  reader->current_line.len = bytesRead;
  s8_parsed out = {0};
  out.str = reader->current_line;
  out.ok = 1;
  return out;
}

void destroy_line_reader(line_reader *reader) {
  free(reader->line_buffer.data);
  reader->line_buffer.len = 0;
  free(reader->current_line.data);
  fclose(reader->file);
  free(reader);
}
