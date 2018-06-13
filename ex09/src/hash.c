#include "hash.h"
#include <stddef.h>
#include <stdlib.h>
#include "linked_list.h"

hashtable_t     *hash_create(unsigned int size) {
  hashtable_t *new_table;

  if (size < 1)
    return NULL;

  if((new_table = malloc(sizeof(hashtable_t))) == NULL)
    return NULL;

  new_table->table = malloc(size*sizeof(node_t*));

  for(int i = 0; i < size; i++)
    new_table->table[i] = NULL;

  new_table->size = size;

    return new_table;
}

void            hash_destroy(hashtable_t *ht, void (*fp)(void *data)) {
  for(int i = 0; i < ht->size; i++) {
    if (ht->table[i] != NULL) {
      node_t *ptr = ht->table[i];
      list_destroy(&ptr, fp);
    }
  }

  free(ht->table);
  free(ht);
}

unsigned int    hash_func(char *key) {
  if (key == NULL) return 0;
  unsigned int rv = 0;

  while (*key != '\0') {
    rv += *key;
    key++;
  }

  return rv;
}

void            hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data)) {
  int index = hash_func(key) % ht->size;

  fp(ptr);

  if(ht->table[index] == NULL) ht->table[index] = list_create(ptr);
  else
    list_push(ht->table[index], ptr);
}

void            *hash_get(hashtable_t *ht, char *key) {
  int index = hash_func(key) % ht->size;

  if(ht->table[index] == NULL) return NULL;


  return ((node_t*)ht->table[index])->data;
}