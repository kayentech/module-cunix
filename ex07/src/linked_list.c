#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

node_t *list_create(void *data) {
  node_t *curr = malloc(sizeof(node_t));
  if(curr == NULL) return NULL;
  curr->data = data;
  curr->next = NULL;
  return curr;
}

void list_destroy(node_t **head, void (*fp)(void *data)){
  if(*head == NULL) return;
  node_t *curr = *head;
  head = NULL;
  node_t *del;
  while (curr != NULL) {
    fp(curr->data);
    del = curr;
    curr = curr->next;
    free(del);
  }
}

void list_push(node_t *head, void *data) {
  if(head == NULL) return;
  node_t *curr = head;
  node_t *new_node = malloc(sizeof(node_t));
  while(curr->next != NULL) curr=curr->next;
  new_node->data = data;
  new_node->next = NULL;
  curr->next = new_node;
}

void list_unshift(node_t **head, void *data) {
  node_t *first = malloc(sizeof(node_t));
  first->data = data;
  first->next = *head;
  *head = first;
}

void *list_pop(node_t **head) {
  if(*head == NULL) return NULL;
  if((*head)->next == NULL) {
    free(*head);
    *head = NULL;
    return NULL;
  }
  node_t *curr = *head;
  while(curr->next->next != NULL){
    curr = curr->next;
  }
  free(curr->next->data);
  free(curr->next);
  curr->next = NULL;
}

void list_print(node_t *head) {
  node_t *curr = head;
  while(curr != NULL) {
    printf("%s\n", curr->data);
    curr = curr->next;
  }
}

void *list_shift(node_t **head) {
  if(*head == NULL) return NULL;
  node_t* curr = *head;
  *head = curr->next;
  free(curr->data);
  free(curr);
}

void *list_remove(node_t **head, int pos) {
  if(*(head) == NULL) return NULL;
  if(pos == 0) return list_shift(head);
  node_t *p = *head;
  node_t *cur = (*head)->next;
  for(int num = 1; num != pos; num++) {
    p = p->next;
    cur = cur->next;
  }
  p->next = cur->next;
  free(cur->data);
  free(cur);
}

void list_visitor(node_t *head, void (*fp)(void *data)) {
  while(head) {
    fp(head->data);
    head = head->next;
  }
};
