// File: queue.c
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Implements a queue

#include <stdlib.h>
#include "queue.h"

// Creates a new Queue
Queue *newQueue() {
  Queue *q = malloc(sizeof(Queue));
  q->L = newList();
  // head will be front of queue (first in line)
  return q;
}

// Basic necesseties...
int sizeQ(const Queue *q) {
  return q->L->size;
}

int emptyQ(const Queue *q) {
  return empty(q->L);
}

// Core functions for a Queue
void insertQ(Queue *q, void *item) { // Add to back (list tail)
  append(q->L, item);
}

void *removeQ(Queue *q) { // Remove from front of queue
  removeFirst(q->L);
}
