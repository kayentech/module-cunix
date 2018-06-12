#include "../include/linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
node_t  *list_create(void *data)
{
  node_t *head = (node_t *) malloc(sizeof(node_t)) ;
  head->data = data;
  head->next = NULL;
  return head;
}

void    list_destroy(node_t **head, void (*fp)(void *data))
{
  fp(*head);
}

void    list_push(node_t *head, void *data)
{
  node_t * cur_elem = head;
  while ( cur_elem->next != NULL )
    cur_elem = cur_elem->next;
  cur_elem->next = (node_t *) malloc(sizeof(node_t));
  cur_elem->next->data = data;
  cur_elem->next->next = NULL;
}
void    list_unshift(node_t **head, void *data)
{
  node_t *tmp = (node_t *) malloc (sizeof(node_t));
  tmp->data = data;
  tmp->next = *head;
  *head = tmp;
}
void   *list_pop(node_t **head)
{
  node_t *cur_elem = *head;
  while (cur_elem->next->next != NULL)
    cur_elem = cur_elem->next;
  free(cur_elem->next);
  cur_elem->next = NULL;
}
void   *list_shift(node_t **head)
{
  node_t *tmp = *head;
  *head = tmp->next;
  free(tmp);
}
void   *list_remove(node_t **head, int pos)
{
  node_t *cur_elem = *head;
  int i = 0;
  while (i < pos){
    cur_elem = cur_elem->next;
    i++;
  }
  node_t *tmp = cur_elem->next;
  cur_elem->next = tmp->next;
  free(tmp);
}
void    list_print(node_t *head)
{
  node_t *tmp = head;
  while (tmp->next != NULL){
      printf(tmp->data);
      tmp = tmp->next;
  }
}
void    list_visitor(node_t *head, void (*fp)(void *data))
{
 node_t *cur_elem = head;
 while (cur_elem->next != NULL){
   fp(cur_elem->data);
   cur_elem = cur_elem->next;
 }
}
