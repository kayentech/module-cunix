#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_t  *allocnode() {
  node_t *ptr = malloc(sizeof(node_t));

  ptr->left = NULL;
  ptr->right = NULL;
  ptr->data = NULL;
  ptr->key = NULL;

  return ptr;
}

node_t  *insert(node_t *root, char *key, void *data) {
  if (root == NULL) {
    node_t *ptr = malloc(sizeof(node_t));
    ptr->key = key;
    ptr->data = data;
    ptr->left = NULL;
    ptr->right = NULL;

    return ptr;
  }

  if(strcmp(root->key, key) < 0) {
    root->right = insert(root->right, key, data);
  }
  else {
    root->left = insert(root->left, key, data);
  }

  return root;
}

void    print_node(node_t *node) {
  if(node == NULL) return;
  printf("%s - > %s", node->key, (char*)node->data);
}

void    visit_tree(node_t *node, void (*fp)(node_t *root)) {
  if(node == NULL) return;
  fp(node);
  visit_tree(node->left, fp);
  visit_tree(node->right, fp);
}

void    destroy_tree(node_t *node, void (*fdestroy)(node_t *root)) {
  if(node == NULL) return;
  destroy_tree(node->left, fdestroy);
  destroy_tree(node->right, fdestroy);
  fdestroy(node);
  free(node);
}