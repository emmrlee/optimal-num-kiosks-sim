// File: desGenTable.c
// Author: Emma Lee
// Date Created: 12/5/2023
// Purpose: Assignment 6
/* Implements a discrete event simulation of an airport check-in hall for
 * the given number of minutes for varying number of kiosks (simulations
 * of each number of kiosks will have NUM_RUNS runs each).
 * The final output of the program will be a table of these runs,
 * where each column represents a simulation with a different # kiosks;
 * each row represents the a single run
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kiosk.h"
#include "queue.h"

#define MAX_NUM_CUST 3 // the max amount of customers that can arrive in one minute
#define NUM_RUNS 10 // the number of runs per each simulation
#define MAX_CELL_LEN 12 // the max length of a table cell n1/n2/x
#define MAX_TABLE_LEN 5 // the maximum amount of columns (besides header) to print
#define NUM_TABLES_TO_PRINT 4 // the number of tables to be printed
#define MAX_NUM_KIOSKS MAX_TABLE_LEN*NUM_TABLES_TO_PRINT
// to simulate up to N kiosks, N must = MAX_TABLE_LEN*NUMTABLES_TO_PRINT
// ex: to simulate different kiosk numbers 1-20, if MAX_TABLE_LEN is 5, NUM_TABLES_TO_PRINT should be 4

// returns the num of customers that arrived in any given minute
int arrival();

// runs the simulation for m minutes on k kiosks & returns a table cell n1/n2/x
char *genTableCell(int nMin, int nKiosk);

// handles table formatting by printing a table for nMin for the given range of #kiosks [start, end]
void printTableFrom(int nMin, int start, int end);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int nMin = atoi(argv[1]);

  // want to keep table readable (small enough to fit on screen)
  // thus, only print a table for MAX_TABLE_LEN different #kiosks at a time
  for (int i = 1; i < MAX_NUM_KIOSKS; i+=MAX_TABLE_LEN) {
    printTableFrom(nMin, i, i+MAX_TABLE_LEN-1);
    printf("\n");
  }
  
  return 0;
} // main()

int arrival() { // returns the number of customers that arrived (any value [0..3])
  return rand() % (MAX_NUM_CUST + 1);
}  

// simulate for m minutes on k kiosks & returns a table cell string in the format n1/n2/x
char *genTableCell(int nMin, int nKiosk) { 
  // create k kiosks
  Kiosk *kiosks[nKiosk];
  for (int i=0; i < nKiosk; i++)
    kiosks[i] = newKiosk();
  
  // create a queue of customers
  Queue *checkInQueue;
  checkInQueue = newQueue();
  int queueLength = 0; // total of all queue lengths during simulation
  int nCust = 0; // total customers arrived

  // for each minute…
  for (int t=1; t <= nMin; t++) {
    // n Customers arrive
    int n = arrival();

    // create and add each customer to the queue
    for (int i = 1; i <= n; i++) {
      Customer *c = newCustomer(t);
      insertQ(checkInQueue, c);
      nCust++;
    }
    
    // assign customers to kiosks
    for (int k = 0; k < nKiosk; k++) {
      if (!busy(kiosks[k]) && !emptyQ(checkInQueue)) {
	assignCustomer(kiosks[k], removeQ(checkInQueue));
      }
    }

    // check the current queue length & record
    queueLength += sizeQ(checkInQueue);
    
    // serve customers/kiosks run for 1 minute
    for (int k = 0; k < nKiosk; k++)
      tick(kiosks[k]);
  }

  int nServed = 0;
  for (int k = 0; k < nKiosk; k++)
    nServed += getNServed(kiosks[k]);
  
  char *result = malloc(MAX_CELL_LEN * sizeof(char));
  sprintf(result, "%d/%d/%.1f", nCust, nServed, (float) queueLength/nMin);
  return result;
} // simulate()

// handles table formatting by printing a table for nMin the given range of #kiosks [start, end]
void printTableFrom(int nMin, int start, int end) {
  // print header row
  printf("#Kiosks\t");
  for (int i = start; i <= end; i++)
    printf("%-15d\t", i);
  printf("\n");

  // for each run [1..NUM_RUNS]
  for (int i = 1; i <= NUM_RUNS; i++) {
    printf("Run #%d\t", i);
    // for each # kiosk, simulate and print table cell n1/n2/x
    // n1: #arrived, n2: #served, x: avg queue len
    for (int nKiosk = start; nKiosk <= end; nKiosk++) {
      printf("%-15s\t", genTableCell(nMin, nKiosk));
    }
    printf("\n");
  }
} //printTableFrom()
