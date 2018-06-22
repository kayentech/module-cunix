#ifndef   HASH_H_
# define  HASH_H_

typedef struct  hashtable {
  unsigned int  size;
  void          **table;
  // int           backend_type; //0 noop for test, 1 linkedlist, 2 tree
  //void          (*fcreate)();
  //void          (*fseek)(char *key);
  //void          (*fdestroy)();
  //void          (*fhash)(char *k);
}               hashtable_t;

hashtable_t     *hash_create(unsigned int size);
void            hash_destroy(hashtable_t *ht, void (*fp)(void *data));
unsigned int    hash_func(char *key);

void            hash_set(hashtable_t *ht, char *key, void *ptr);
void            *hash_get(hashtable_t *ht, char *key);

#endif
