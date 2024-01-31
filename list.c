// File: list.c
// Author: Emma Lee
// Date Created: 12/6/2023
// Purpose: Assignment 6
// Implements a list

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List *newList() {
  List *L = malloc(sizeof(List));
  L->head = NULL;
  L->tail = NULL;
  L->size = 0;
  return L;
}

int size(const List *l) {
  return l->size;
}

int empty(const List *l) {
  return l->size == 0;
}

void append(List *l, void *item) { // append
  struct node *n = newNode(item);
  if (l->size == 0) // list empty
    l->head = l->tail = n;
  else { // not empty
    l->tail->next = n;
    l->tail = n;
  }
  l->size++;
}

void *removeFirst(List *l) {
  if (empty(l))
    return NULL;

  struct node *n = l->head;
  void *item = n->data;
  struct node *next = l->head->next;
  free(n);
  l->head = next;
  l->size--;
  return item;
}

void *get(const List *l, int index) {
  if (index < 0 || index >= l->size) {
    printf("Error: List index out of bounds %d. Exiting!\n", index);
    exit(EXIT_FAILURE);
  }

  struct node *n = l->head;
  for (int i = 0; i < index; i++) 
    n = n->next;
  return n->data;
}

void clear(List *l) {
  struct node *n = l->head;
  struct node *next;
  while (n != NULL) {
    next = n->next;
    free(n);
    n = next;
  }
  l->head = l->tail = NULL;
  l->size = 0;
}
