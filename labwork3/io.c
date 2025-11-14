#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "io.h"

char* inputLine(void) {
    size_t size = 128, len = 0;
    char *buf = malloc(size);
    if (!buf) return NULL;

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        buf[len++] = c;
        if (len >= size - 1) {
            size *= 2;
            char *nb = realloc(buf, size);
            if (!nb) { free(buf); return NULL; }
            buf = nb;
        }
    }
    if (len == 0 && c == EOF) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}

double inputNumber(InputType type) {
    while (1) {
        printf(type == DOUBLE ? "Введите число: " : "Введите целое: ");

        char *s = inputLine();
        if (!s) continue;

        char *end;
        double v = strtod(s, &end);
        while (*end && isspace(*end)) end++;

        if (*end != '\0') {
            printf("Ошибка ввода.\n");
            free(s);
            continue;
        }
        free(s);

        if (type == INT && floor(v) != v) {
            printf("Ожидалось целое.\n");
            continue;
        }
        return v;
    }
}

void* inputArray(InputType type, int *count) {
    while (1) {
        printf("Введите числа через пробел: ");
        char *line = inputLine();
        if (!line) continue;

        int cnt = 0;
        char *tmp = strdup(line);
        char *tok = strtok(tmp, " ");
        while (tok) { cnt++; tok = strtok(NULL, " "); }
        free(tmp);

        if (cnt == 0) { free(line); continue; }

        void *arr = calloc(cnt, type == DOUBLE ? sizeof(double) : sizeof(int));
        tok = strtok(line, " ");
        int i = 0;
        int ok = 1;

        while (tok) {
            char *end;
            if (type == DOUBLE) {
                double v = strtod(tok, &end);
                while (*end && isspace(*end)) end++;
                if (*end != '\0') ok = 0;
                ((double*)arr)[i++] = v;
            } else {
                long v = strtol(tok, &end, 10);
                while (*end && isspace(*end)) end++;
                if (*end != '\0') ok = 0;
                ((int*)arr)[i++] = (int)v;
            }
            tok = strtok(NULL, " ");
        }
        free(line);

        if (!ok) { free(arr); continue; }

        *count = cnt;
        return arr;
    }
}