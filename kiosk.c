// File: kiosk.c
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Implements a kiosk that serves customers

#include <stdio.h>
#include <stdlib.h>
#include "kiosk.h"
#include "customer.h"

#define DEBUG 0

static int kCount = 0;

char *genKioskId() { // creates a unique id as 'K' + count
  kCount++;
  char *id = malloc(5*sizeof(char)); // Max 4-letters for ID +1 for '\0'
  sprintf(id, "K%d", kCount);
  return id;
}

// Create a new Kiosk: K#
Kiosk *newKiosk() {
  Kiosk *k = malloc(sizeof(Kiosk));
  k->nowServing = NULL;
  k->timeRemaining = 0;
  k->id = genKioskId();
  k->nServed = 0;
  return k;
}

// accessors
char *getKioskId(const Kiosk *k) {
  return k->id;
}

Customer *getCustomer(const Kiosk *k) {
  return k->nowServing;
}

int getNServed(const Kiosk *k) {
  return k->nServed;
}

// assign customer c to kiosk k
void assignCustomer(Kiosk *k, Customer *c) {
  k->nowServing = c;
  k->timeRemaining = c->serviceTime;
}

// performs 1 minute of service to customer (if serving one)
// if customer is completely served, it resets this kiosk (to no customer)
void tick(Kiosk *k) {
  if (k->timeRemaining > 0) {
    k->timeRemaining--;
    if (k->timeRemaining == 0) { // just finished serving a customer
      k->nServed++;
      #if DEBUG
      printf("FINISHED SERVING %s, NSERVED for %s IS %d\n", k->id, k->id, k->nServed);
      #endif
    }
  } else {
    k->nowServing = NULL;
  }
}

int busy(const Kiosk *k) { // is Kiosk, k serving a customer?
  return k->nowServing != NULL;
}

// print representation of a Kiosk is K12: <C19: 42, 8> [3]
char *kioskToString(const Kiosk *k) {
  char *result = malloc(20*sizeof(char));
  if (busy(k)) // there is a customer
    sprintf(result, "%s: %s [%d]", k->id, custToString(k->nowServing), k->timeRemaining);
  else
    sprintf(result, "%s: [%d]", k->id, k->timeRemaining);
  return result;
}
