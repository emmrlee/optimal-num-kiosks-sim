// File: node.c
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Implements a node

#include <stdlib.h>
#include "node.h"

struct node *newNode(void *data) {
  struct node *n = malloc(sizeof(struct node));
  n->data = data;
  n->next = NULL;
}
