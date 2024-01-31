// File: list.h
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Designs a list

#ifndef LIST_H
#define LIST_H

#include "node.h"

typedef struct {
  int size;
  struct node *head;
  struct node *tail;
} List;

List *newList(); // Creates a new empty list
int size(const List *l); // Returns the size of list-l
int empty(const List *l); // is the list-l empty?
void clear(List *l); // removes all items from list-l
void append(List *l, void *item); // Adds given item to the end of list-l
void *removeFirst(List *l); // Remove item from front of list-l and return a pointer to its data
void *get(const List *l, int index); // Returns pointer to the item at index in list-l
#endif
