#include "hash.h"
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

hashtable_t *hash_create(unsigned int size) {
  if( size < 1 ) return NULL;
  hashtable_t *ht = malloc(size * sizeof(hashtable_t));
  ht->table = malloc(size * sizeof(node_t*));
  for( int i = 0; i < size; i++ ) ht->table[i] = NULL;
  ht->size = size;
  return ht;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data)) {
  for( int i = 0; i < ht->size; i++ ) {
    if(ht->table[i]) {
      node_t *ptr = ht->table[i];
      list_destroy(&(ptr), fp);
    }
  }
  free(ht->table);
  free(ht);
}

unsigned int hash_func(char *key) {
  if( !key ) return 0;
  unsigned int answer = 0;
  while( *key != '\0' ) {
    answer += *key;
    key++;
  }
  return answer;
}

void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data)) {
  int index = hash_func(key)%ht->size;
  fp(ptr);
  if ( !(ht->table[index]) ) ht->table[index] = list_create(ptr);
  else list_push(ht->table[index], ptr);
}

void *hash_get(hashtable_t *ht, char *key) {
  int index = hash_func(key)%ht->size;
  if( !(ht->table[index]) ) return NULL;
  node_t *ptr = ht->table[index];
  return ptr->data;
}
