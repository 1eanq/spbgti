#include <stdio.h>
#include "array.h"
#include "utils.h"

void printArray(void *arr, int n, InputType t) {
    for (int i = 0; i < n; i++)
        printf(t == INT ? "%d " : "%8.2lf ", 
               t == INT ? ((int*)arr)[i] : ((double*)arr)[i]);
    printf("\n");
}

void cyclicShift(double *arr, int n, int k, int right) {
    if (!arr || n <= 1) return;

    k %= n;
    if (!right) k = n - k;

    for (int i=0,j=n-1;i<j;i++,j--) swap(&arr[i],&arr[j]);
    for (int i=0,j=k-1;i<j;i++,j--) swap(&arr[i],&arr[j]);
    for (int i=k,j=n-1;i<j;i++,j--) swap(&arr[i],&arr[j]);
}