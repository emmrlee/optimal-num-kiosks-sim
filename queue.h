// File: queue.h
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Defines a queue

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct {
  List *L;
} Queue; // A Queue is just a linked list

// Creates a new Queue
Queue *newQueue();

// Basic necesseties...
int sizeQ(const Queue *q);
int emptyQ(const Queue *q);

// Core functions for a Queue
void insertQ(Queue *q, void *item);
void *removeQ(Queue *q);

#endif
