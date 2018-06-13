#include "linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

node_t  *list_create(void *data) {
  node_t *head = malloc(sizeof(node_t));

  head->data = data;
  head->next = NULL;

  return head;
}

void    list_destroy(node_t **head, void (*fp)(void *data)) {
  if(*head == NULL) return;
  node_t *ptr = *head, *pptr;

  while(ptr != NULL) {
    fp(ptr->data);
    pptr = ptr->next;
    free(ptr);
    ptr = pptr;
  }
  (*head) = NULL;
}

void    list_push(node_t *head, void *data) {
  if (head == NULL) return;
  while (head->next) head = head->next;
  head->next = malloc(sizeof(node_t));

  head = head->next;
  head->next = NULL;
  head->data = data;
}

void    list_unshift(node_t **head, void *data) {
  node_t *ptr = *head;

  *head = malloc(sizeof(node_t));

  (*head)->next =  ptr;
  (*head)->data = data;
}

void    *list_pop(node_t **head) {
  node_t *ptr, *pptr = *head;
  void *rv;

  if(pptr->next) {
    ptr = pptr->next;
  }
  else {
    rv = (*head)->data;
    free((*head)->data);
    free(*head);
    *head = NULL;
    return rv;
  }
  while (ptr->next) {
    ptr = ptr->next;
    pptr = pptr->next;
  }
  rv = ptr->data;
  free(ptr->data);
  free(ptr);
  pptr->next = NULL;
  return rv;
}

void    *list_shift(node_t **head) {
  if (*head == NULL) return NULL;
  void *rv;
  node_t *ptr = *head;

  (*head) = (*head)->next;

  rv = ptr->data;
  free(ptr->data);
  free(ptr);

  return rv;
}

void    *list_remove(node_t **head, int pos) {
  void *rv;
  node_t *ptr = *head, *pptr;
  if (pos == 0) {
    rv = ptr->data;
    (*head) = (*head)->next;
    free(ptr->data);
    free(ptr);
    return rv;
  }

  pptr = ptr;
  ptr = ptr->next;

  while(pos > 1) {
    ptr = ptr->next;
    pptr = pptr->next;
    pos--;
  }

  pptr->next = ptr->next;
  rv = ptr->data;
  free(ptr->data);
  free(ptr);

  return rv;
}

void    list_print(node_t *head) {
  while(head) {
    printf("%s\n", (char*)head->data);
    head = head->next;
  }
}

void    list_visitor(node_t *head, void (*fp)(void *data)) {
  while(head) {
    fp(head->data);
    head = head->next;
  }
}