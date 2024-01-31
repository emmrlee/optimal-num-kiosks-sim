// File: node.h
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Designs a node

#ifndef NODE_H
#define NODE_H

struct node {
  void *data;
  struct node *next;
};

struct node *newNode(void *data);

#endif
