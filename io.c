#include "io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

function FILE *open(const byte *name) {
  FILE *file = fopen(name, "r");
  if (file == NULL) {
    assert(0);
    return NULL;
  }
  return file;
};

LineReader *createLineReader(const char *filename, size_t line_buffer_size) {
  LineReader *reader = malloc(sizeof(LineReader));
  if (reader == NULL) {
    perror("Error creating LineReader");
    exit(EXIT_FAILURE);
  }

  reader->file = fopen(filename, "r");
  if (reader->file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  reader->line_buffer = malloc(line_buffer_size);
  if (reader->line_buffer == NULL) {
    perror("Error creating line buffer");
    exit(EXIT_FAILURE);
  }

  reader->line_buffer_size = line_buffer_size;
  reader->current_line.data = NULL;
  reader->current_line.len = 0;

  return reader;
}

void destroyLineReader(LineReader *reader) {
  free(reader->line_buffer);
  free(reader->current_line.data);
  fclose(reader->file);
  free(reader);
}

// TODO change to s8_parsed
s8 readNextLine(LineReader *reader) {
  size bytesRead;

  // Read a line into the buffer
  if (fgets(reader->line_buffer, (i32)reader->line_buffer_size, reader->file) ==
      NULL) {
    // End of file
    printf("EOF");
    return (s8){NULL, 0};
  }

  bytesRead = strlen(reader->line_buffer);

  // Allocate or reallocate memory for the line
  reader->current_line.data = realloc(reader->current_line.data, bytesRead);
  if (reader->current_line.data == NULL) {
    perror("Error allocating memory for line");
    exit(EXIT_FAILURE);
  }

  // Copy the line from the buffer to the allocated memory
  s8copy(reader->current_line.data, reader->line_buffer, bytesRead); // TODO
  reader->current_line.len = bytesRead;

  return reader->current_line;
}
