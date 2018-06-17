#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


node_t *allocnode() {
  node_t *curr = malloc(sizeof(node_t));
  curr->left = NULL;
  curr->right = NULL;
  return curr;
}

node_t *insert(node_t *root, char *key, void *data) {
  if(!root) {
    node_t *newNode = allocnode();
    newNode->key = key;
    newNode->data = data;
    return newNode;
  }
  node_t **next = (strcmp(root->key,key) > 0) ? (next = &root->left) : (next = &root->right);
  *next = insert(*next, key, data);
  return root;
};

void print_node(node_t *node) {
  if(!node) return;
  print_node(node->left);
  print_node(node->right);
  printf("%s : %s\n", (char*)node->data, (char*)node->key);
};
void visit_tree(node_t *node, void (*fp)(node_t *root)) {
  if(!node) return;
  fp(node);
  visit_tree(node->left, fp);
  visit_tree(node->right, fp);
};

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root)) {
  if(!node) return;
  fdestroy(node);
  if(node->left)
    destroy_tree(node->left, fdestroy);
  if(node->right)
    destroy_tree(node->right, fdestroy);
  free(node);
}
