#include <stdio.h>
#include "array.h"

int main (int argc, char *argv[]) {
  
  long capacity = 2;
  Array myArray = array_new(capacity);
  array_print(myArray);

  long data = 10;
  array_insertBack(&myArray, data);
  array_insertBack(&myArray, data);
  array_insertBack(&myArray, data);
  array_insertBack(&myArray, data);
  array_insertBack(&myArray, data);
  array_print(myArray);

  /* RESULTAT
  
  Uten  -fsanitize=address:
       * Arrayen blir større og større, til tross for kapasiteten vi satte når den skaptes
  Med  -fsanitize=address:
       * Får nå error: heap-buffer-overflow on address 0x602000000100 at pc 0x0001036f1b24 bp 0x7ffeec510420 sp 0x7ffeec510418
       * 0x602000000100 is located 0 bytes to the right of 16-byte region [0x6020000000f0,0x602000000100)
       * allocated by thread T0 here:
          #0 0x10373cabd in wrap_malloc (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x45abd)
            #1 0x1036f031d in array_new array.c:14
            #2 0x1036f1b9a in main task-b.c:7
            #3 0x7fff67933cc8 in start (libdyld.dylib:x86_64+0x1acc8)
  */
  return 0;
}