// This program prints Hello World! to the screen the number of
// times entered on the command line or NUMTIMES, which ever is greater
#include <stdio.h>  // need to link stdio.h to get printf function
#include <stdlib.h> // need to link stdlib.h to get atoi function
#define NUMTIMES 5  // a named constant value (compiler replacement)

int hworld (int howmany) {  // Function to print“Hello World!” howmany times
    int i;                  // loop control variable, a local memory address
    for (i=0; i < howmany; i++)
        printf("Hello World!\n");
    return 0;
}

int main (int argc, char *argv[]){  // accept command line arguments
    int inputval = 0;
    if (argc > 1) inputval = atoi(argv[1]);  // save value from command line

    if (NUMTIMES > inputval) {
        hworld(NUMTIMES);
    } else {
        hworld(inputval);
    }
    return 0;
}
