#include <stdlib.h>
#include "random.h"

double* randomDoubleArray(int n, double min, double max) {
    double *a = calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        a[i] = min + (max - min) * (rand() / (double)RAND_MAX);
    return a;
}

int* randomIntArray(int n, int min, int max) {
    int *a = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = min + rand() % (max - min + 1);
    return a;
}