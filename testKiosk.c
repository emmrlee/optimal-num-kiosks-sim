// File: testKiosk.c
// Author: Emma Lee
// Date Created: 12/4/2023
// Purpose: Assignment 6
// Tests kiosk

#include <stdio.h>
#include "kiosk.h"

int main(void) {
  Kiosk *ks[5];
  for (int i=0; i < 5; i++) {
    ks[i] = newKiosk();
  }
  
  for (int i=0; i < 5; i++) {
    printf("<%s: %d>\n", ks[i]->id, ks[i]->timeRemaining);
    printf("%s\n", kioskToString(ks[i]));
  }

  Customer *cs[5]; // We will create 5 customers
  int t = 23;
  for (int i=0; i < 5; i++) {
    cs[i] = newCustomer(t);
    t++;
  }

  printf("Adding customers...\n");
  for (int i=0; i < 5; i++) {
    assignCustomer(ks[i], cs[i]);
  }

  for (int i=0; i < 5; i++) {
    printf("<%s: %d>\n", ks[i]->id, ks[i]->timeRemaining);
    printf("%s\n", kioskToString(ks[i]));
  }

  printf("Serving customer at first kiosk (k[0])\n");
  printf("ks[0] is busy?: %d\n", busy(ks[0])); // 1
  tick(ks[0]);
  while (busy(ks[0]))
    tick(ks[0]);
  printf("ks[0] is busy?: %d\n", busy(ks[0])); // 0

  getNServed(ks[0]); // 1

  for (int i=0; i < 5; i++) {
    printf("<%s: %d>\n", ks[i]->id, ks[i]->timeRemaining);
    printf("%s\n", kioskToString(ks[i]));
  }
    
  return 0;
} // main()
