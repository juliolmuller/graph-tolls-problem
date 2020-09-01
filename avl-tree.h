#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  int value;
  struct _node *left, *right;
  int height;
} TreeNode;

TreeNode *tree_create_node(int value)
{
  TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  node->height = 0;

  return node;
}

int max_node_value(int a, int b)
{
  return (a > b) ? a : b;
}

int tree_height(TreeNode *node)
{
  return node ? node->height : -1;
}

TreeNode *tree_turn_right(TreeNode *root)
{
  TreeNode *aux = root->left;
  root->left = aux->right;
  aux->right = root;
  root->height = max_node_value(tree_height(root->left), tree_height(root->right)) + 1;
  aux->height = max_node_value(tree_height(aux->left), root->height) + 1;

  return aux;
}

TreeNode *tree_turn_left(TreeNode *root)
{
  TreeNode *aux = root->right;
  root->right = aux->left;
  aux->left = root;
  root->height = max_node_value(tree_height(root->right), tree_height(root->left)) + 1;
  aux->height = max_node_value(tree_height(aux->right), root->height) + 1;

  return aux;
}

TreeNode *tree_turn_right_left(TreeNode *root)
{
  root->right = tree_turn_right(root->right);
  return tree_turn_left(root);
}

TreeNode *tree_turn_left_right(TreeNode *root)
{
  root->left = tree_turn_left(root->left);
  return tree_turn_right(root);
}

void tree_print(TreeNode *root)
{
  if (root) {
    printf("%i", root->value);
    printf(" (");
    tree_print(root->left);
    tree_print(root->right);
    printf(") ");
  }
}

TreeNode *tree_search_node(TreeNode *root, int value)
{
  if (!root)
    return NULL;
  if (value < root->value)
    return tree_search_node(root->left, value);
  if (value > root->value)
    return tree_search_node(root->right, value);

  return root;
}

int tree_count_nodes(TreeNode *root)
{
  if (root == NULL) {
    return 0;
  }

  return 1 + tree_count_nodes(root->left) + tree_count_nodes(root->right);
}

TreeNode *tree_add_node(TreeNode *root, TreeNode *node)
{
  if (!root)
    return node;

  if (node->value < root->value) {
    root->left = tree_add_node(root->left, node);

    if (tree_height(root->left) - tree_height(root->right) == 2) {
      if (node->value < root->left->value)
        root = tree_turn_right(root);
      else
        root = tree_turn_left_right(root);
    }
  } else if (node->value > root->value) {
    root->right = tree_add_node(root->right, node);

    if (tree_height(root->right) - tree_height(root->left) == 2) {
      if (node->value > root->right->value)
        root = tree_turn_left(root);
      else
        root = tree_turn_right_left(root);
    }
  }
  root->height = max_node_value(tree_height(root->left), tree_height(root->right)) + 1;

  return root;
}

TreeNode *tree_search_node2(TreeNode *root, int value, TreeNode **parent)
{
  TreeNode *current = root;
  *parent = NULL;

  while (current) {
    if (value == current->value)
      return current;

    *parent = current;
    if (value < current->value)
      current = current->left;
    else
      current = current->right;
  }

  return NULL;
}

TreeNode *tree_remove_node(TreeNode *root, int value)
{
  TreeNode *parent, *node, *next, *aux;
  node = tree_search_node2(root, value, &parent);

  if (!node)
    return root;

  if (!node->left || !node->right) {
    next = node->left ? node->left : node->right;
  } else {
    aux = node;
    next = node->left;

    while (next->right) {
      aux = next;
      next = next->right;
    }

    if (aux != node) {
      aux->right = next->left;
      next->left = node->left;
    }
    next->right = node->right;
  }

  if (!parent) {
    free(node);

    return next;
  }

  if (value < parent->value)
    parent->left = next;
  else
    parent->right = next;


  free(node);

  return root;
}

int add_to_list(TreeNode *node, int arr[], int index)
{
  if (!node)
    return index;

  if (node->left != NULL)
    index = add_to_list(node->left, arr, index);
  arr[index++] = node->value;
  if (node->right != NULL)
    index = add_to_list(node->right, arr, index);

  return index;
}
