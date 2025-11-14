#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"
#include "io.h"
#include "array.h"
#include "matrix.h"
#include "random.h"

static int countEven(int x) { return (x % 2 == 0); }

/* -------------------------------- TASK 1 ----------------------------- */

void task1(int test) {
    int n;

    if (test) {
        n = rand() % 7 + 3;
    } else {
        printf("Введите количество элементов: ");
        n = (int)inputNumber(INT);
    }

    int count;
    double *arr = test ?
        randomDoubleArray(n, -5, 5) :
        inputArray(DOUBLE, &count);

    if (!test && count != n) { printf("Неверная длина!\n"); free(arr); return; }

    double **m = calloc(n, sizeof(double*));
    for (int i = 0; i < n; i++) {
        m[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
            m[i][j] = arr[j];
        cyclicShift(m[i], n, i, 0);
    }

    printMatrix(m, n, n);

    freeMatrix(&m, n);
    free(arr);
}

/* -------------------------------- TASK 2 ----------------------------- */

#define LEN 8

void task2(int test) {
    int *arr = NULL;
    int count = LEN;

    arr = test ?
        randomIntArray(LEN, -9, 9) :
        inputArray(INT, &count);

    if (!test && count != LEN) {
        printf("Нужно ровно %d чисел!\n", LEN);
        free(arr);
        return;
    }

    for (int i = 0; i < LEN; i += 2)
        arr[i] |= (1 << i);

    printArray(arr, LEN, INT);
    free(arr);
}

/* -------------------------------- TASK 3 ----------------------------- */

void task3(int test) {
    int count;
    int *arr = test ?
        randomIntArray((rand()%6)+5, -9, 9) :
        inputArray(INT, &count);

    if (test)
        count = count;

    int *filtered = calloc(count, sizeof(int));
    int pos = 0;
    for (int i = 0; i < count; i++)
        if (countEven(arr[i]))
            filtered[pos++] = arr[i];

    printArray(filtered, pos, INT);

    free(arr);
    free(filtered);
}