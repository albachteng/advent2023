#include "s8.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARENA_SIZE 1024

function void s8print(s8 str) {
  for (ptrdiff_t i = 0; i < str.len; i++) {
    putchar(str.data[i]);
  }
}

function b32 s8equals(s8 first, s8 second) {
  if (first.len != second.len) {
    return 0;
  }
  for (ptrdiff_t i = 0; i < first.len; i++) {
    if (first.data[i] != second.data[i])
      return 0;
  }
  return 1;
};

function s8 s8clone(s8 src) {
  s8 dst;
  dst.data = (char *)malloc(src.len + 1);
  if (dst.data == NULL) {
    printf("error in malloc for s8copy");
    exit(1);
  }
  strncpy(dst.data, src.data, src.len);
  dst.data[src.len] = '\0';
  dst.len = src.len;
  return dst;
};

function s8 s8postfix(s8 src, char ch) {
  s8 our;
  our.data = (char *)malloc(src.len +
                            2); // +2 for the new character and null terminator
  if (our.data == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  strncpy(our.data, src.data, src.len);
  our.data[src.len] = ch;
  our.data[src.len + 1] = '\0';
  our.len = src.len + 1;
  return our;
};

function s8 s8slice(s8 src, ptrdiff_t beg, ptrdiff_t end) {
  s8 out;
  if (beg >= src.len || beg > end) {
    return out; // TODO
  }
  ptrdiff_t len = (end > beg) ? (end - beg) : 0; // TODO silent failures here...
  printf("len = %td\n", len);
  out.data = (char *)malloc(len + 1);
  if (out.data == NULL) {
    exit(1); // TODO
  }
  strncpy(out.data, src.data + beg, len);
  out.data[len] = '\0';
  out.len = len;
  return out;
}

// function s8 s8prefix(s8 src, char ch){
//
// };

function s8list *s8list_init() {
  arena ar = init_arena();
  s8list *lst = new (&ar, s8list, 1);
  lst->arena = ar;
  lst->head = NULL;
  lst->tail = NULL;
  return lst;
};

function s8list *s8list_reset(s8list *lst) {
  lst->arena.end = lst->arena.beg;
  lst->head = NULL;
  lst->tail = NULL;
  return lst;
}

function s8 *s8_from_char(char *ch) {
  s8 *str = (s8 *)malloc(sizeof(s8));
  str->data[0] = *ch;
  str->data[1] = '\0';
  str->len = 1;
  return str;
}

// add string to list in-place
function void s8list_append(s8list *list, s8 *str) {
  s8node *node = new (&list->arena, s8node, 1);
  node->val = s8clone(*str);
  node->next = NULL;
  // printf("printing node in append");
  // s8print(node->val);
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}

// new list
function s8list *s8list_merge(s8list *first, s8list *second) {
  s8list *out = s8list_init();
  s8node *curr = first->head;
  while (curr != NULL) {
    s8list_append(out, &curr->val);
    curr = curr->next;
  }
  curr = second->head;
  while (curr != NULL) {
    s8list_append(out, &curr->val);
    curr = curr->next;
  }
  return out;
};

function void s8list_print(s8list *list) {
  s8node *curr = list->head;
  while (curr != NULL) {
    s8print(curr->val);
    curr = curr->next;
  }
}

function s8list *s8list_slice(s8list *list, ptrdiff_t start, ptrdiff_t end) {
  s8list *out = s8list_init();
  ptrdiff_t idx = 0;
  s8node *curr = list->head;
  while (idx < start && curr != NULL) {
    idx++;
    curr = curr->next;
  }
  while (idx < end && curr != NULL) {
    idx++;
    s8list_append(out, &curr->val);
    curr = curr->next;
  }
  return out;
}

function s8 s8list_to_s8(s8list *list) {
  s8 out;
  char buffer[1024];
  ptrdiff_t pos = 0;
  s8node *curr = list->head;
  while (curr != NULL) {
    for (ptrdiff_t i = 0; i < curr->val.len; i++) {
      // printf("%c\n", curr->val.data[i]);
      printf("%s\n%td\n", buffer, pos);
      buffer[pos++] = curr->val.data[i];
    }
    curr = curr->next;
  }
  buffer[pos] = '\0';
  out.data = buffer;
  out.len = pos;
  return out;
};

// necessary?
function void s8list_free(s8list *list) {
  list->head = NULL;
  list->tail = NULL;
  list->arena.beg = 0; // TODO
}

// int main() {
//   s8 str = s8("hello world");
//   s8 out = s8slice(str, 5, 9);
//   s8print(out);
// }

// returns the character from the string at poition pos
function char_parsed s8at(s8 src, int pos) {
  char_parsed out = (char_parsed){.data = ' ', .ok = 0};
  if (src.len < pos || pos < 0) {
    return out;
  }
  out.data = src.data[pos];
  out.ok = 1;
  return out;
};
