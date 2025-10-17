#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>


#define N 4
#define M 5

typedef enum {
    MENU_EXIT = 0,
    MENU_FIRST_TASK = 1,
    MENU_SECOND_TASK = 2,
    MENU_THIRD_TASK = 3,
    MENU_TEST = 4,
    MENU_TEST_SECOND_TASK = 5,
    MENU_TEST_THIRD_TASK = 6
} MenuOption;

typedef enum {
    INPUT_DOUBLE,
    INPUT_NATURAL
} InputType;

void showMenu() {
    printf("\n=== Главное меню ===\n");
    printf("1. Задача 1\n");
    printf("2. Задача 2\n");
    printf("3. Задача 3\n");
    printf("4. Тест\n");
    printf("5. Тест 2 задачи\n");
    printf("6. Тест 3 задачи\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

char* inputLine(void) {
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

    if (c == EOF && len == 0) {  // пустой ввод
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

void* inputArray(InputType type, int* outCount) {
    while (1) {
        if (type == INPUT_DOUBLE)
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
        if (type == INPUT_DOUBLE)
            arr = calloc(count, sizeof(double));
        else
            arr = calloc(count, sizeof(int));

        if (!arr) {
            free(line);
            line = NULL;
            *outCount = 0;
            return NULL;
        }

        token = strtok(line, " ");
        int i = 0, error = false;
        while (token) {
            char* endptr;
            if (type == INPUT_DOUBLE) {
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
        arr = NULL;
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
    int lenN, lenD;
    int* n = NULL;
    double* d = NULL;

    if (!autogen) {
        n = (int*)inputArray(INPUT_NATURAL, &lenN);
        d = (double*)inputArray(INPUT_DOUBLE, &lenD);

        if (!n || !d) {
            printf("Ошибка: не удалось получить входные данные.\n");
            free(n);
            n = NULL;
            free(d);
            d = NULL;
            return;
        }

        if (lenN != lenD) {
            printf("Ошибка: количество элементов n (%d) и d (%d) должно совпадать.\n", lenN, lenD);
            free(n);
            n = NULL;
            free(d);
            d = NULL;
            return;
        }
    } else {
        lenN = lenD = 5 + rand() % 5;
        n = calloc(lenN, sizeof(int));
        d = calloc(lenD, sizeof(double));

        if (!n || !d) {
            printf("Ошибка выделения памяти.\n");
            free(n);
            n = NULL;
            free(d);
            d = NULL;
            return;
        }

        printf("Автогенерация для task2:\n");
        printf("n: ");
        for (int i = 0; i < lenN; i++) {
            n[i] = 1 + rand() % 10;
            printf("%d ", n[i]);
        }
        printf("\nd: ");
        for (int i = 0; i < lenD; i++) {
            d[i] = (rand() % 200 - 100) / 10.0;
            printf("%.2f ", d[i]);
        }
        printf("\n");
    }

    int len = lenN;
    double dividend = 0.0;
    int divisor = 0;
    for (int i = 0; i < len; i++) {
        dividend += n[i] * d[i];
        divisor += n[i];
    }

    if (divisor == 0) {
        printf("Ошибка: сумма элементов n равна нулю, деление невозможно.\n");
    } else {
        printf("Результат: %f\n", dividend / divisor);
    }

    free(n);
    n = NULL;
    free(d);
    d = NULL;
}

void task3(int autogen) {
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
                row = (double*)inputArray(INPUT_DOUBLE, &count);
                if (row != NULL && count == M) break;
                printf("Ошибка: нужно ввести ровно %d чисел. Попробуйте снова.\n", M);
                free(row);
                row = NULL;
            }
            for (int j = 0; j < M; j++) G[i][j] = row[j];
            free(row);
            row = NULL;
        }
    } else {
        printf("Автогенерация матрицы для task3:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                double val = (rand() % 200 - 100) / 10.0;
                if (rand() % 8 == 0) val = 0.0;
                G[i][j] = val;
            }
        }
    }

    printf("\nНачальная матрица G:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) printf("%8.2f ", G[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        double prod = 1;
        int count = 0;
        int hasZero = 0;

        for (int j = 0; j < M; j++) {
            if (fabs(G[i][j]) < 1e-6) {
                G[i][j] = (double)count;
                hasZero = true;
                break;
            } else {
                prod *= G[i][j];
                count++;
            }
        }

        if (hasZero)
            a[i] = (count > 0) ? prod : 0;
        else
            a[i] = 0;
    }

    // === Вывод преобразованной матрицы ===
    printf("\nПреобразованная матрица G:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) printf("%8.2f ", G[i][j]);
        printf("\n");
    }

    // === Вывод вектора a ===
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
    setlocale(LC_CTYPE, "RU");

    printf("Название: main.c\nЗадание: Контрольная работа №2 вар. 7\nАвтор: И. Д. Горинов, СПбГТИ (ТУ), 2025\n");

    MenuOption choice;
    int running = true;

    while (running) {
        showMenu();
        int input;
        if (scanf("%d", &input) != 1) {
            while (getchar() != '\n');
            printf("Ошибка ввода! Попробуйте снова.\n");
            continue;
        }
        while (getchar() != '\n');

        choice = (MenuOption)input;

        switch (choice) {
            case MENU_FIRST_TASK: task1(); break;
            case MENU_SECOND_TASK: task2(false); break;
            case MENU_THIRD_TASK: task3(false); break;
            case MENU_TEST: test(); break;
            case MENU_TEST_SECOND_TASK: task2(true); break;
            case MENU_TEST_THIRD_TASK: task3(true); break;
            case MENU_EXIT: running = false; break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }

    return EXIT_SUCCESS;
}
