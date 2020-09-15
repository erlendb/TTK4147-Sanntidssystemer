#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
  // The program below allocates memory for a very large 8GB matrix of 64-bit integers:
  long xy_size  = 1000*1000*1000;     // 8 GB (sizeof(long) = 8 bytes)
  long x_dim    = 100;
  long y_dim    = xy_size/x_dim;

  long** matrix = malloc(y_dim*sizeof(long*)); 

  for (long y = 0; y < y_dim; y++){
    matrix[y] = malloc(x_dim*sizeof(long));
    memset(matrix[y], 0, x_dim*sizeof(long));
  }

  printf("Allocation complete (press any key to continue...)\n");
  getchar();

  /* --- */
  // TODO:
  // * Open the System Monitor from Dash (aka the ”start menu”), and go to theresources tab. From here you can see the total memory used by the system.  Run the program, andobserve the effects on the memory usage.  Don’t worry if the computer becomes unresponsive, it’sjust old and needs some time.
  // * What happens?
  // Memory usage increases fast, then swap usage increases. PCen henger seg opp. Tar lang tid til alt er allokert.
  //
  // * What is the difference between ”Memory” and ”Swap”?
  // Swap: the virtual memory allocated on the hard drive when the RAM is full
  // Memory: RAM
  //
  // * Now change the shape of the matrix by increasing xdim first to 1000, then 10000, and run theprogram again.  What happens?
  // 1000: Minnebruk øker raskt til ca 65%. PCen henger ikke. Swap alltid på under 20%
  // 10000: Minnebruk 20% (????), swap stabilt på under 20%. Veldig raskt. 
  // 
  // * Run the program with xdim= 10000 again, but this time write zeros to all the memory:
  //    memset(matrix[y], 0, x_dim*sizeof(long));
  // Oppførselen ligner veldig på x_dim=100. Bruker mye minne, treigt, henger seg opp.
  // Ender opp med 100% memory og ca 25% swap

  // RESULTAT:
  // * Memory = RAM, Swap = "Memory" placed on disk space, while it is not in use
  // * Uten memset: bruker veldig lite minne. Malloc allokerer Virtuell RAM, så det meste ligger i SWAP?
  // * Med memset: OS allokerer RAM ved første write?
  // * Fra stackoverflow: "In most OSes neither allocates RAM. They both allocate VM space. They make a certain range of your processes virtual memory valid for use. RAM is normally allocated later by the OS on first write. Until then those allocations do not use RAM (aside from the page table that lists them as valid VM space)."

  return 0;
}