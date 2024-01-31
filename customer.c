// File: customer.c
// Author: Emma Lee
// Date Created: 12/1/2023
// Purpose: Assignment 6
// Implements a customer

#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

static int cCount = 0;

int randInt(int start, int end) {
  return start + (rand() % (end - start));
}

// private helper function to be used by newCustomer()
// (thus does not need to be listed in protos for customer.h
char *genCustId() { // creates a unique id as 'C' + count (e.g. C23, C9, etc.)
  cCount++;
  char *id = malloc(5*sizeof(char)); // Max 4-letters for ID +1 for '\0'
  sprintf(id, "C%d", cCount);
  return id;
} // genCustId()

// Given arrival time, create a new customer
Customer *newCustomer(int arrTime) {
  Customer *c = malloc(sizeof(Customer));
  c->arrivalTime = arrTime; // Creates a new customer, with an ID (up to 4 chars), whose
  c->serviceTime = randInt(5,8);
  // arrival time is arrTime, and service time is between 5-8 minutes (random)
  c->id = genCustId();
  return c;
}

int getArrivalTime(const Customer *c) {
  return c->arrivalTime;
}

int getServiceTime(const Customer *c) {
  return c->serviceTime;
}

char *getCustId(const Customer *c) {
  return c->id;
}

// Print Representation
char *custToString(const Customer *c) {
  // Print form: <id: arrivalTime, serviceTime> (e.g. <C23: 12, 7>, <C19, 42, 8>, etc.)
  char *result = malloc(20*sizeof(char));
  sprintf(result, "<%s: %d, %d>", c->id, c->arrivalTime, c->serviceTime);
  return result;
}
