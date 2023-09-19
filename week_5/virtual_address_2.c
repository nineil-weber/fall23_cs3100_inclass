//
// Created by NilsMurrugarra-Llerena on 9/26/22.
//

#include <stdio.h>
#include <stdlib.h>

int InitializedGlobal[1024] = {0,};
int UnintGlobal[1024];

int main() {
    int localVar1;
    int localVar2;
    int *dynamicLocalVar1;
    int *dynamicLocalVar2;

    dynamicLocalVar1 = (int *) malloc(sizeof(int));
    dynamicLocalVar2 = (int *) malloc(sizeof(int));

    printf("code                 : 0x%x\n", main);
    printf("Data                 : 0x%x\n", &InitializedGlobal);
    printf("BSS(Uninit Data)     : 0x%x\n", &UnintGlobal);

    printf("stack localVar1      : 0x%x\n", &localVar1);
    printf("stack localVar2      : 0x%x\n", &localVar2);
    printf("heap dynamicLocalVar1: 0x%x\n", dynamicLocalVar1);
    printf("heap dynamicLocalVar2: 0x%x\n", dynamicLocalVar2);
    return 0;
}
