#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void freeMatrix(double ***m, int n) {
    if (!m || !*m) return;
    for (int i = 0; i < n; i++) free((*m)[i]);
    free(*m);
    *m = NULL;
}

void printMatrix(double **m, int n, int M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < M; j++)
            printf("%8.2lf ", m[i][j]);
        printf("\n");
    }
}