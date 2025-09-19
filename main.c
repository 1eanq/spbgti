#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
//#include <windows.h>

#define INPUT_SIZE 512

void donut() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for(;;) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
}

double inputDouble(const char *prompt) {
    char input[INPUT_SIZE];
    char *endptr;
    double val;

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            val = strtod(input, &endptr);

            while (*endptr != '\0' && isspace(*endptr)) {
                endptr++;
            }

            if (*endptr == '\0' || *endptr == '\n') {
                return val;
            }
            printf("Ошибка: введено не число. Попробуйте ещё раз.\n");
        }
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

    printf("Результат: %lf\n", result);
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


    printf("Результат: %lf\n", result);}

void task3() {
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
        printf("(%lf,%lf)\n", x, y);
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
        } else if (choice >= 0 && choice <= 4) {
            while ((ch = getchar()) != '\n' && ch != EOF);
            return choice;
        } else {
            printf("Ошибка: выберите число от 0 до 3!\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

int main() {
    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);

    int choice;
    do {
        choice = chooseTask();

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: donut(); break;
            case 0: printf("Выход из программы.\n"); break;
        }

    } while (choice != 0);

    return 0;
}
