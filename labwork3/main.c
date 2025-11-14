#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"

void init(void) {
    setlocale(LC_CTYPE, "");
    srand((unsigned)time(NULL));
    printf("Контрольная работа №3 вар. 7\nАвтор: И. Д. Горинов, СПбГТИ (ТУ), 2025\n");
}

void shutdown(void) {
    printf("\n----------Выход из программы----------\n");
}

int main() {
    init();
    runMenu();
    shutdown();
    return 0;
}