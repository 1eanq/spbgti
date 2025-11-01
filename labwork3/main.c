#include <stdio.h>
#include "main.h"

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH 8

void showMenu() {
    printf("\n=== Главное меню ===\n");
    printf("1. Задача 1\n");
    printf("2. Задача 2\n");
    printf("3. Задача 3\n");
    //printf("4. Тест\n");
    //printf("5. Тест 2 задачи\n");
    //printf("6. Тест 3 задачи\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

double inputNumber(InputType type) {
    while (1) {
        if (type == DOUBLE)
            printf("Введите действительное число: ");
        else
            printf("Введите целое число: ");

        char* line = inputLine();
        if (!line) {
            printf("Ошибка ввода.\n");
            continue;
        }

        char* endptr;
        double value = strtod(line, &endptr);

        while (*endptr && isspace((unsigned char)*endptr)) endptr++;

        if (*endptr != '\0') {
            printf("Ошибка: некорректное число '%s'. Попробуйте снова.\n", line);
            free(line);
            continue;
        }

        free(line);

        if (type == INT) {
            if (floor(value) != value) {
                printf("Ошибка: ожидалось целое число.\n");
                continue;
            }
        }

        return value;
    }
}

char* inputLine() {
    size_t size = 128;
    size_t len = 0;
    char* buffer = malloc(size);
    if (!buffer) return NULL;

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        buffer[len++] = (char)c;

        if (len >= size - 1) {
            size *= 2;
            char* newbuf = realloc(buffer, size);
            if (!newbuf) {
                free(buffer);
                buffer = NULL;
                return NULL;
            }
            buffer = newbuf;
        }
    }

    if (c == EOF && len == 0) {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

void* inputArray(InputType type, int* outCount) {
    while (1) {
        if (type == DOUBLE)
            printf("Введите действительные числа через пробел: ");
        else
            printf("Введите натуральные числа через пробел: ");

        char* line = inputLine();
        if (!line) {
            *outCount = 0;
            return NULL;
        }

        int count = 0;
        char* temp = strdup(line);
        if (!temp) {
            free(line);
            line = NULL;
            *outCount = 0;
            return NULL;
        }
        char* token = strtok(temp, " ");
        while (token) {
            count++;
            token = strtok(NULL, " ");
        }
        free(temp);
        temp = NULL;

        if (count == 0) {
            printf("Ошибка: нет введённых чисел. Попробуйте снова.\n");
            free(line);
            line = NULL;
            continue;
        }

        void* arr = NULL;
        if (type == DOUBLE)
            arr = calloc((size_t)count, sizeof(double));
        else
            arr = calloc((size_t)count, sizeof(int));

        if (!arr) {
            free(line);
            line = NULL;
            *outCount = 0;
            return NULL;
        }

        token = strtok(line, " ");
        int i = 0;
        bool error = false;
        while (token) {
            char* endptr;
            if (type == DOUBLE) {
                double val = strtod(token, &endptr);
                while (*endptr && isspace((unsigned char)*endptr)) endptr++;
                if (*endptr != '\0') {
                    printf("Ошибка: '%s' не действительное число.\n", token);
                    error = true;
                    break;
                }
                ((double*)arr)[i++] = val;
            } else {
                long val = strtol(token, &endptr, 10);
                while (*endptr && isspace((unsigned char)*endptr)) endptr++;
                if (*endptr != '\0' || val <= 0) {
                    printf("Ошибка: '%s' не натуральное число.\n", token);
                    error = true;
                    break;
                }
                ((int*)arr)[i++] = (int)val;
            }
            token = strtok(NULL, " ");
        }

        free(line);
        line = NULL;

        if (!error) {
            *outCount = count;
            return arr;
        }

        free(arr);
        arr = NULL;
        printf("Попробуйте снова.\n");
    }
}

 void init(void) {
    setlocale(LC_CTYPE, "");

    srand((unsigned)time(NULL));

    printf("Название: main.c\nЗадание: Контрольная работа №3 вар. 7\nАвтор: И. Д. Горинов, СПбГТИ (ТУ), 2025\n");
}

void freeMatrix(double ***matrix, int N) {
    if (matrix == NULL || *matrix == NULL)
        return;

    for (int i = 0; i < N; i++) {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }

    free(*matrix);
    *matrix = NULL;
}

void inputMatrix(double ***matrix, int N, int M) {
    *matrix = (double **)malloc(N * sizeof(double *));
    if (*matrix == NULL) {
        printf("Ошибка выделения памяти.\n");
        freeMatrix(matrix, N);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        (*matrix)[i] = (double *)malloc(M * sizeof(double));
        if ((*matrix)[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            freeMatrix(matrix, N);
            exit(1);
        }

        printf("Введите %d элементов для строки %d: ", M, i + 1);
        for (int j = 0; j < M; j++) {
            if (scanf("%lf", &(*matrix)[i][j]) != 1) {
                printf("Неверный ввод!\n");
                freeMatrix(matrix, N);
                exit(1);
            }
        }
    }
}

void printMatrix(double **matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%8.3lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArray(void *arr, int size, InputType type) {
    if (!arr || size <= 0) return;

    for (int i = 0; i < size; i++) {
        if (type == INT)
            printf("%d ", ((int*)arr)[i]);
        else if (type == DOUBLE)
            printf("%8.3lf ", ((double*)arr)[i]);
    }
    printf("\n");
}

void cyclicShift(double *arr, int size, int k, bool direction) {
    if (!arr || size <= 1) return;

    k %= size;
    if (k == 0) return;

    if (!direction)
        k = size - k;

    for (int i = 0, j = size - 1; i < j; i++, j--)
        swap(&arr[i], &arr[j]);

    for (int i = 0, j = k - 1; i < j; i++, j--)
        swap(&arr[i], &arr[j]);

    for (int i = k, j = size - 1; i < j; i++, j--)
        swap(&arr[i], &arr[j]);
}

void task1(void) {
    printf("Введите количество элементов.\n");
    int m = (int)inputNumber(INT);

    double *arr = NULL;

    bool incorrect = true;
    while (incorrect) {
        int outcount = 0;
        arr = (double *)inputArray(DOUBLE, &outcount);
        if (arr == NULL) {
            exit(1);
        }
        if (outcount != m) {
            printf("Неверная длинна строки! %d != %d", outcount, m);
            continue;
        }
        incorrect = false;
    }

    double **matrix = (double **)calloc(m, sizeof(double *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
        if (!matrix[i]) {
            printf("Ошибка выделения памяти для строки %d.\n", i);
            freeMatrix(&matrix, i);
            free(arr);
            return;
        }

        for (int j = 0; j < m; j++)
            matrix[i][j] = arr[j];

        cyclicShift(matrix[i], m, i, false);
    }

    printMatrix(matrix, m, m);

    freeMatrix(&matrix, m);
}

void task2(void) {
    printf("Введите %d целых чисел через пробел: ", LENGTH);
    int *arr = NULL;

    bool incorrect = true;
    while (incorrect) {
        int outcount = 0;
        arr = (int *)inputArray(INT, &outcount);
        if (arr == NULL) {
            free(arr);
            exit(1);
        }
        if (outcount != LENGTH) {
            printf("Неверная длинна строки! %d != %d", outcount, LENGTH);
            free(arr);
            continue;
        }
        incorrect = false;
    }
    for (int i = 1; i <= LENGTH; i += 2) {
        arr[i] |= (1 << (i - 1));
    }

    printArray(arr, LENGTH, INT);
}

bool isEven(int n) {
    return (n % 2) == 0;
}

int filter(const int *src, int size, Predicate pred, int *dst) {
    if (!src || !dst || size <= 0 || !pred) return 0;

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (pred(src[i])) {
            dst[count++] = src[i];
        }
    }
    return count;
}

void task3(void) {
    int *arr = NULL;
    int outcount = 0;

    bool incorrect = true;
    while (incorrect) {
        arr = (int *)inputArray(INT, &outcount);
        if (arr == NULL) {
            free(arr);
            exit(1);
        }
        incorrect = false;
    }

    int *dst = calloc(outcount, sizeof(int));

    int newSize = filter(arr, outcount, isEven, dst);

    printArray(dst, newSize, INT);

    free(dst);
}

void run(void) {
    Menu menu;
    bool running = true;

    while (running) {
        showMenu();
        int option;
        if (scanf("%d", &option) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Ошибка ввода! Попробуйте снова.\n");
            continue;
        }
        int ch;
        while ((ch = getchar()) != EOF && ch != '\n');
        menu = (Menu)option;

        switch (menu) {
            case MENU_EXIT: running = false; break;
            case MENU_FIRST_TASK: task1(); break;
            case MENU_SECOND_TASK: task2(); break;
            case MENU_THIRD_TASK: task3(); break;
            default: printf("Неверный выбор! Попробуйте снова.\n");

        }
    }
}

int main() {
    init();

    run();

    printf("\n");
    printf("----------Выход из программы----------");
    printf("\n");

    return EXIT_SUCCESS;
}