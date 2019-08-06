#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include <assert.h>

void printInt(void *data)
{
  printf("%s\n", (char *)data);
}

void test_destroy_push(void *data)
{
  free(data);
}

void test_destroy_noop(void *data)
{
  data = data;
}

void test_debug_print(void *data)
{
  printf("DEBUG: %s\n", (char *) data);
}

int test_create()
{
  node_t  *head;
  char    *valid;

  head = list_create("test");
  valid = head->data;
  list_destroy(&head, &test_destroy_noop);
  return strcmp(valid, "test");
}

int test_destroy()
{
  node_t *head;

  head = list_create("Test destroy: fail");
  list_destroy(&head, &test_destroy_noop);
  return 0;
}

int test_push()
{
  node_t  *head;
  char    *str;

  asprintf(&str, "head");
  head = list_create(str);

  for(int i = 1; i <= 10; i++)
  {
    asprintf(&str, "%05d-hello\n", i);
    list_push(head, str);
  }

  list_print(head);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_print()
{
  node_t *head;
  char   *str;

  asprintf(&str, "Test ");
  head = list_create(str);
  asprintf(&str, "print: ");
  list_push(head, str);
  asprintf(&str, "ok");
  list_push(head, str);
  list_print(head);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_unshift()
{
  node_t *head;
  char   *str;

  asprintf(&str, "head");
  head = list_create(str);

  for(int i = 0; i < 10; i++)
  {
    asprintf(&str, "%05d-world\n", i);
    list_unshift(&head, str);
  }

  asprintf(&str, "Test unshift: ok");
  list_unshift(&head, str);
  list_print(head);
  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_pop()
{
  node_t  *head;
  char    *str;

  asprintf(&str, "head");
  head = list_create(str);

  asprintf(&str, "Test pop: fail");
  list_push(head, str);

  asprintf(&str, "Test pop: ok");
  list_push(head, str);

  list_pop(&head);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_shift()
{
  node_t   *head;
  char     *str;

  asprintf(&str, "Test shift: fail");
  head = list_create(str);
  asprintf(&str, "Test shift: ok");
  list_push(head, str);

  list_shift(&head);
  list_shift(&head);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_remove()
{
  node_t *head;
  char   *str;

  asprintf(&str, "head");
  head = list_create(str);

  asprintf(&str, "1");
  list_push(head, str);
  asprintf(&str, "2");
  list_push(head, str);
  asprintf(&str, "Test remove: ok");
  list_push(head, str);
  asprintf(&str, "4");
  list_push(head, str);
  asprintf(&str, "5");
  list_push(head, str);

  list_remove(&head, 3);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_visitor()
{
  node_t *head;
  char   *str;

  asprintf(&str, "Test visitor: ok");
  head = list_create(str);
  list_visitor(head, &test_debug_print);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int test_global()
{
  node_t *head;
  char   *str;

  asprintf(&str, "Test global: ok");
  head = list_create(str);


  for(int i = 0; i < 10000; i++)
  {
    asprintf(&str, "Unshifting %d", i);
    list_unshift(&head, str);
  }


  for(int i = 0; i < 10000; i++)
  {
    asprintf(&str, "Pushing");
    list_push(head, str);
  }

  for(int i = 0; i < 10000; i++)
    list_pop(&head);

  for(int i = 0; i < 10000; i++)
    list_shift(&head);

  list_destroy(&head, &test_destroy_push);

  return 0;
}

int main()
{
   assert(test_create() == 0);
   assert(test_destroy() == 0);
   assert(test_push() == 0);
   assert(test_print() == 0);
   assert(test_unshift() == 0);
   assert(test_pop() == 0);
   assert(test_shift() == 0);
   assert(test_remove() == 0);
   assert(test_visitor() == 0);
   assert(test_global() == 0);
  return (0);
}
