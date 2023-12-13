#include "base.h"
#include "s8.c"
#include <stddef.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 1024

function ptrdiff_t hash(s8 key) {
  int out = 0;
  while (*key.data)
    out = (out << 5) + *key.data++;
  return out % HASHTABLE_SIZE;
}

typedef struct {
  int val;
  b32 ok;
} parsed_int;

typedef struct HashNode {
  s8 key;
  int val;
  struct HashNode *next;
} HashNode;

typedef struct {
  ptrdiff_t size;
  arena arena;
  HashNode *buckets[HASHTABLE_SIZE];
} HashTable;

function HashTable *init_hashtable() {
  HashTable *tbl = (HashTable *)malloc(sizeof(HashTable));
  tbl->arena = init_arena();
  for (ptrdiff_t i = 0; i < HASHTABLE_SIZE; i++) {
    tbl->buckets[i] = NULL;
  }
  tbl->size = 0;
  return tbl;
};

function void append(HashNode *head, HashNode *toAdd) {
  HashNode *curr = head;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = toAdd;
};

function HashNode *create_node(HashTable *tbl, s8 key, int val) {
  HashNode *node = new (&tbl->arena, HashNode, 1);
  node->key = key;
  node->val = val;
  node->next = NULL;
  return node;
}

function void hash_set(HashTable *tbl, s8 key, int val) {
  HashNode *node = create_node(tbl, key, val);
  ptrdiff_t hsh = hash(key);
  if (!tbl->buckets[hsh])
    tbl->buckets[hsh] = node;
  else {
    // TODO - collisions
    append(tbl->buckets[hsh], node);
  }
  tbl->size++;
}

function parsed_int hash_get(HashTable *tbl, s8 key) {
  ptrdiff_t hsh = hash(key);
  parsed_int out = {0, 0};
  HashNode *curr = tbl->buckets[hsh];
  while (curr != NULL) {
    if (s8equals(curr->key, key)) {
      out.val = curr->val;
      out.ok = 1;
      return out;
    }
    curr = curr->next;
  }
  return out;
}
