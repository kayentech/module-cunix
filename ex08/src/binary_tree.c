#include "binary_tree.h"
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <assert.h>

node_t  *allocnode()
{
  node_t *new;
  new=malloc(sizeof(node_t));
  new->left=NULL;
  new->right=NULL;
  return new;
}

node_t *insert(node_t *root, char *key, void *data)
	{
	    if(root == NULL)
	    {
			root = allocnode();
			root->key = key;
			root->data = data;
	   	}
	    	else if(root->key >= key)
	     		root->right = insert(root->right, key, data);
	    	else
		    	root->left = insert(root->left, key, data);
    	return root;
	}
void    print_node(node_t *node)
{
  if (node==NULL)
  {
    return ;
  }
  else
  {
    printf("%p\n",node->data);
  }

}
void    destroy_tree(node_t *node, void (*fdestroy)(node_t *root))
  {
    if (node->left!=NULL)
    {
      if(node->right!=NULL)
      {
        destroy_tree(node->right,fdestroy);
        destroy_tree(node->left,fdestroy);
      }
      else
      {
        destroy_tree(node->left,fdestroy);
      }
    }
    else
    {
      if (node->right!=NULL)
      {
        destroy_tree(node->right,fdestroy);
      }
    }
    fdestroy(node);
    free(node);
  }
void    visit_tree(node_t *node, void (*fp)(node_t *root))
{
  if (node->left!=NULL)
  {
    if(node->right!=NULL)
    {
      visit_tree(node->right,fp);
      visit_tree(node->left,fp);
    }
    else
    {
      visit_tree(node->left,fp);
    }
  }
  else
  {
    if (node->right!=NULL)
    {
      visit_tree(node->right,fp);
    }
  }
  fp(node);
}
