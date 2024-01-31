// File: des.c
// Author: Emma Lee
// Date Created: 12/5/2023
// Purpose: Assignment 6
/* Implements a discrete event simulation of an airport check-in hall -
 * in each minute, up to 3 customers can arrive and queue up - with varied
 * number of kiosks to find the optimal number so that the average queue
 * lenght is no more than 3 customers
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kiosk.h"
#include "queue.h"

#define MAX_NUM_CUST 3 // the max amount of customers that can arrive in one minute
#define DEBUG 0

// returns the num of customers that arrived in any given minute
int arrival();

// runs the simulation for m minutes on k kiosks
void simulate(int nMin, int nKiosk);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int nMin = atoi(argv[1]);
  int nKiosk = atoi(argv[2]);
  simulate(nMin, nKiosk);
  return 0;
} // main()

int arrival() { // returns the number of customers that arrived (any value [0..3])
  return rand() % (MAX_NUM_CUST + 1);
}  

void simulate(int nMin, int nKiosk) { // simulate for m minutes on k kiosks
  // create k kiosks
  Kiosk *kiosks[nKiosk];
  for (int i=0; i < nKiosk; i++)
    kiosks[i] = newKiosk();

  #if DEBUG
    printf("There are %d kiosks.", nKiosk);  
    printf("[ "); // print out each kiosk
    for (int i=0; i < nKiosk; i++)
      printf("%s ", kioskToString(kiosks[i]));
    printf("]\n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n");
  #endif
  
  // create a queue of customers
  Queue *checkInQueue;
  checkInQueue = newQueue();
  int queueLength = 0; // total of all queue lengths during simulation
  int nCust = 0; // total customers arrived

  // for each minute…
  for (int t=1; t <= nMin; t++) {
    // n Customers arrive
    int n = arrival();

    #if DEBUG
      printf("Adding %d customers...\n", n);
    #endif
    
    // create and add each customer to the queue
    for (int i = 1; i <= n; i++) {
      Customer *c = newCustomer(t);
      insertQ(checkInQueue, c);
      nCust++;
    }

    #if DEBUG
      printf("The running total count of customers (nCust) is %d\n", nCust);
      printf("At time %d there are %d customers on Q\n\n", t, sizeQ(checkInQueue));
    #endif
    
    // assign customers to kiosks
    for (int k = 0; k < nKiosk; k++) {
      if (!busy(kiosks[k]) && !emptyQ(checkInQueue)) {
	assignCustomer(kiosks[k], removeQ(checkInQueue));
      }
    }

    // check the current queue length & record
    queueLength += sizeQ(checkInQueue);

    #if DEBUG
      printf("After assigning customer(s) to open kiosk(s), the current Q length is %d\n", sizeQ(checkInQueue));
      printf("The total of all queue lenghts (queueLength) is %d\n", queueLength);
    #endif
    
    // serve customers/kiosks run for 1 minute
    for (int k = 0; k < nKiosk; k++)
      tick(kiosks[k]);

    #if DEBUG
      printf("[ "); // print out status of all kiosks
      for (int i=0; i < nKiosk; i++)
        printf("%s ", kioskToString(kiosks[i]));
      printf("]\n");
      printf("--------------------------------------------------------------------------\n");
      printf("\n");
    #endif    
  }

  int nServed = 0;
  for (int k = 0; k < nKiosk; k++)
    nServed += getNServed(kiosks[k]);
  
  printf("Simulation: %d minutes, with %d kiosks\n", nMin, nKiosk);
  printf("%d customers arrived.\n", nCust);
  printf("%d customers served.\n", nServed);
  printf("Average queue length: %.1f\n", (float) queueLength/nMin);
} // simulate()
