#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
//#include <windows.h>

#define INPUT_SIZE 256

typedef enum {
    MENU_EXIT = 0,
    MENU_FIRST_TASK = 1,
    MENU_SECOND_TASK = 2,
    MENU_THIRD_TASK = 3,
    MENU_TEST = 4
} MenuOption;

void showMenu() {
    printf("\n=== Главное меню ===\n");
    printf("1. Задача 1\n");
    printf("2. Задача 2\n");
    printf("3. Задача 3\n");
    printf("4. Тест\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

double* inputDoubleArray(int* outCount) {
    char line[INPUT_SIZE];

    while (1) {
        printf("Введите действительные числа через пробел: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            *outCount = 0;
            return NULL;
        }

        line[strcspn(line, "\n")] = '\0';

        int count = 0;
        char* temp = strdup(line);
        char* token = strtok(temp, " ");
        while (token) {
            count++;
            token = strtok(NULL, " ");
        }
        free(temp);

        if (count == 0) {
            printf("Ошибка: нет введённых чисел. Попробуйте снова.\n");
            continue;
        }

        double* arr = malloc(count * sizeof(double));
        if (!arr) {
            *outCount = 0;
            return NULL;
        }

        token = strtok(line, " ");
        int i = 0, error = 0;
        while (token) {
            char* endptr;
            double val = strtod(token, &endptr);
            while (*endptr != '\0' && isspace((unsigned char)*endptr)) endptr++;

            if (*endptr != '\0') {
                printf("Ошибка: '%s' не действительное число.\n", token);
                error = 1;
                break;
            }

            arr[i++] = val;
            token = strtok(NULL, " ");
        }

        if (!error) {
            *outCount = count;
            return arr;
        }

        free(arr);
        printf("Попробуйте снова.\n");
    }
}

int* inputNaturalArray(int* outCount) {
    char line[INPUT_SIZE];

    while (1) {
        printf("Введите натуральные числа через пробел: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            *outCount = 0;
            return NULL;
        }

        line[strcspn(line, "\n")] = '\0';

        int count = 0;
        char* temp = strdup(line);
        char* token = strtok(temp, " ");
        while (token) {
            count++;
            token = strtok(NULL, " ");
        }
        free(temp);

        if (count == 0) {
            printf("Ошибка: нет введённых чисел. Попробуйте снова.\n");
            continue;
        }

        int* arr = malloc(count * sizeof(int));
        if (!arr) {
            *outCount = 0;
            return NULL;
        }

        token = strtok(line, " ");
        int i = 0, error = 0;
        while (token) {
            char* endptr;
            long val = strtol(token, &endptr, 10);
            while (*endptr != '\0' && isspace((unsigned char)*endptr)) endptr++;

            if (*endptr != '\0' || val <= 0) {
                printf("Ошибка: '%s' не натуральное число.\n", token);
                error = 1;
                break;
            }

            arr[i++] = (int)val;
            token = strtok(NULL, " ");
        }

        if (!error) {
            *outCount = count;
            return arr;
        }

        free(arr);
        printf("Попробуйте снова.\n");
    }
}



void task1(void) {
    double p = 1.0;

    double u1 = 0.4;
    double u2 = 0.5;
    double u3 = 0.93;

    p *= u1;
    p *= u2;
    p *= u3;

    for (int i = 4; i <= 100; i++) {
        double u = sin(u3) + cos(u1);
        p *= u;

        u1 = u2;
        u2 = u3;
        u3 = u;
    }

    printf("p: %f\n", p);
}

void task2(int autogen) {
    int len;
    int* n;
    double* d;

    if (!autogen) {
        n = inputNaturalArray(&len);
        d = inputDoubleArray(&len);
    } else {
        len = 5 + rand() % 5;
        n = malloc(len * sizeof(int));
        d = malloc(len * sizeof(double));

        printf("Автогенерация для task2:\n");
        printf("n: ");
        for (int i = 0; i < len; i++) {
            n[i] = 1 + rand() % 10;
            printf("%d ", n[i]);
        }
        printf("\nd: ");
        for (int i = 0; i < len; i++) {
            d[i] = (rand() % 200 - 100) / 10.0;
            printf("%.2f ", d[i]);
        }
        printf("\n");
    }

    double dividend = 0.0;
    int divisor = 0;
    for (int i = 0; i < len; i++) {
        dividend += n[i] * d[i];
        divisor += n[i];
    }

    printf("Результат: %f\n", dividend / divisor);

    free(n);
    free(d);
}

void task3(int autogen) {
    int N = 4;
    int M = 5;
    double G[N][M];
    double a[N];
    memset(a, 0, sizeof(a));

    if (!autogen) {
        printf("Введите матрицу G (%dx%d):\n", N, M);
        for (int i = 0; i < N; i++) {
            int count;
            double* row;
            while (1) {
                printf("Строка %d: ", i + 1);
                row = inputDoubleArray(&count);
                if (row != NULL && count == M) break;
                printf("Ошибка: нужно ввести ровно %d чисел. Попробуйте снова.\n", M);
                free(row);
            }
            for (int j = 0; j < M; j++) G[i][j] = row[j];
            free(row);
        }
    } else {
        printf("Автогенерация матрицы для task3:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                double val = (rand() % 200 - 100) / 10.0;
                if (rand() % 8 == 0) val = 0.0;
                G[i][j] = val;
                printf("%8.2f ", val);
            }
            printf("\n");
        }
    }

    for (int i = 0; i < N; i++) {
        double prod = 1;
        int count = 0;
        for (int j = 0; j < M; j++) {
            if (fabs(G[i][j]) < 1e-6) {
                G[i][j] = (double)count;
                break;
            } else {
                prod *= G[i][j];
                count++;
            }
        }
        a[i] = (count > 0) ? prod : 0;
    }

    printf("\nВектор a:\n");
    for (int i = 0; i < N; i++) printf("%8.2f ", a[i]);
    printf("\n");
}

void test(void) {
    printf("\n=== Автопроверка всех задач ===\n");

    printf("\n[task1]\n");
    task1();

    printf("\n[task2]\n");
    task2(1);

    printf("\n[task3]\n");
    task3(1);

    printf("\n=== Автопроверка завершена ===\n");
}

int main(void) {
    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);
    setlocale(LC_CTYPE, "RU");

    printf("Название: main.c\nЗадание: Контрольная работа №2 вар. 7\nАвтор: И. Д. Горинов, СПбГТИ (ТУ), 2025");

    MenuOption choice;
    int running = 1;

    while (running) {
        showMenu();
        int input;
        scanf("%d", &input);
        while (getchar() != '\n');

        choice = (MenuOption)input;

        switch (choice) {
            case MENU_FIRST_TASK: task1(); break;
            case MENU_SECOND_TASK: task2(0); break;
            case MENU_THIRD_TASK: task3(0); break;
            case MENU_TEST: test(); break;
            case MENU_EXIT: running = 0; break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }

    return EXIT_SUCCESS;
}