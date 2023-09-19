//
// Created by NilsMurrugarra-Llerena on 9/26/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
//    //Sizeof
//    int *x1 = malloc(10 * sizeof(int)); // TODO: why?
//    printf( "%d\n", sizeof(x1) );
//
//    int x2[10];
//    printf( "%d\n", sizeof(x2) );

//    //Incorrect code --> Segmentation fault
//    char *src="hello";
//    char *dst;
//    strcpy(dst, src);

//    //Correct code
//    char *src="hello";
//    char *dst=(char *)malloc(strlen(src) + 1);
//    strcpy(dst, src);
//    printf("%s\n", dst);

//    //Incorrect code 2
//    char *src="hello";
//    char *dst=(char *)malloc(strlen(src));
//    strcpy(dst, src);
//    printf("%s\n", dst);

//    //Unintialized read
//    int *x=(int *)malloc( sizeof(int) );
////    *x=4;
//    printf("*x = %d\n", *x);

//    // Memory leak
//    while(1)
//    {
//        malloc(4);
//    }

    //Incorrect free --> pointer being freed was not allocated
    int *x = (int *)malloc( sizeof(int) );
    free(x);
    free(x);

    return 0;
}