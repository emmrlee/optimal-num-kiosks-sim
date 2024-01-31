// File: kiosk.h
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Designs a kiosk that serves customers

#ifndef KIOSK_H
#define KIOSK_H

#include "customer.h"

typedef struct {
  char *id;
  Customer *nowServing; // customer this kiosk is serving (or NULL)
  int timeRemaining; // how much time still remains to serve the customer being served
  int nServed; // how many total customers has this specific kiosk served?
} Kiosk;

// create a new Kiosk: K#
Kiosk *newKiosk();

// accessors
char *getKioskId(const Kiosk *k);
Customer *getCustomer(const Kiosk *k);
// returns the customer being served (or NULL)
int getNServed(const Kiosk *k);

void assignCustomer(Kiosk *k, Customer *c);
// assigns customer, c to kiosk, k

void tick(Kiosk *k);
// performs 1 minute of service to customer (if serving one)
// if customer is completely served, it resets this kiosk (to no customer)

int busy(const Kiosk *k);
// is Kiosk, k serving a customer?

// print representation of a Kiosk is K12: <C19: 42, 8> [3]
char *kioskToString(const Kiosk *k);

#endif
