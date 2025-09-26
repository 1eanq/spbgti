/**************************************************
* Название: main.c                                *
* Задание: Контрольная работа №1                  *
* Автор: И. Д. Горинов, СПбГТИ (ТУ), 2025         *
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

#define INPUT_SIZE 512

double inputDouble(const char *prompt) {
    char input[INPUT_SIZE];
    char *endptr;
    double val;

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            val = strtod(input, &endptr);

            while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
                endptr++;
            }

            if (*endptr == '\0' || *endptr == '\n') {
                return val;
            } else {
                printf("Ошибка: введено не число. Попробуйте ещё раз.\n");
            }
        }
    }
}

double normalize(double n) {
    if (n == 0) {
        return 0;
    } else {
        return n;
    }
}

void task1() {
    double x = inputDouble("Введите x: ");
    double y = inputDouble("Введите y: ");

    if (y > 1 || y < -1) {
        printf("y должен быть в пределах [-1 < y < 1].");
        return;
    }

    double dividend = cos(x + y) * pow(x, 3) + 1;
    double  divisor = fabs(exp(x) - (y * 2) / ((pow(x, 2) * pow(y, 2) ) + 1) );

    double result = dividend/divisor + asin(y);

    printf("Результат: %lf\n", normalize(result));
}

void task2() {
    double x = inputDouble("Введите x: ");
    double y = inputDouble("Введите y: ");

    double result = 0;

    if (x < y) {
        result = atan(x + fabs(y));
    } else {
        if (x == y) {
            result = pow(x + y, 2);
        } else {
            result = atan(fabs(x) + y);
        }
    }


    printf("Результат: %lf\n", normalize(result));}

void task3(void) {
    double a = inputDouble("Введите левую границу: ");
    double b = inputDouble("Введите правую границу: ");
    double h = inputDouble("Введите h: ");

    if (a > b) {
        printf("Ошибка! Отрицательный размер множества.");
        return;
    }

    if (h <= 0) {
        printf("Ошибка! Отрицательный шаг.");
        return;
    }

    int steps = floor((b - a)/h);
    double x = a;
    double y;
    for (int i = 0; i <= steps; i++) {
        if (x >= 0) {
            y = sqrt(exp(x) - 1);
        } else {
            y = -1 * pow(x, 2);
        }
        printf("(%lf,%lf)\n", normalize(x), normalize(y));
        x += h;
    }
}

int chooseTask() {
    int choice;
    int ch;

    while (1) {
        printf("\n=== Меню ===\n");
        printf("1. Задача 1\n");
        printf("2. Задача 2\n");
        printf("3. Задача 3\n");
        printf("0. Выход\n");
        printf("Введите номер задачи: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите цифру от 0 до 3!\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else if (choice >= 0 && choice <= 3) {
            while ((ch = getchar()) != '\n' && ch != EOF);
            return choice;
        } else {
            printf("Ошибка: выберите число от 0 до 3!\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

int main(void) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_CTYPE, "RU");

    int choice;
    do {
        choice = chooseTask();

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 0: printf("Выход из программы.\n"); break;
        }

    } while (choice != 0);

    return EXIT_SUCCESS;
}
