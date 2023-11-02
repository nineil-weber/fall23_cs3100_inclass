//
// Created by NilsMurrugarra-Llerena on 10/23/22.
//
#include <stdio.h>

struct Point{
    double x;
    double y;
};

void printPt(struct Point* myPt){
//    printf("\nprintPt: The point is: %f : %f\n",(*myPt).x, (*myPt).y);
    printf("\nprintPt: The point is: %f : %f\n",myPt->x, myPt->y);
}

int main(){

    struct Point p1;

    p1.x = 10;
    p1.y = 30;

    printPt(&p1);
    //printf("\nThe point is: %f : %f\n", p1.x, p1.y);

    return 0;
}
