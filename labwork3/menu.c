#include <stdio.h>
#include "menu.h"

#include <stdbool.h>

#include "tasks.h"

static void showMenu() {
    printf("\n=== Главное меню ===\n");
    printf("1. Задача 1\n");
    printf("2. Задача 2\n");
    printf("3. Задача 3\n");
    printf("4. Тест 1\n");
    printf("5. Тест 2\n");
    printf("6. Тест 3\n");
    printf("0. Выход\n");
    printf("Выберите: ");
}

void runMenu(void) {
    int option;
    while (1) {
        showMenu();

        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch ((Menu)option) {
            case MENU_EXIT: return;
            case MENU_FIRST_TASK: task1(false); break;
            case MENU_SECOND_TASK: task2(false); break;
            case MENU_THIRD_TASK: task3(false); break;
            case MENU_TEST_FIRST_TASK: task1(true); break;
            case MENU_TEST_SECOND_TASK: task2(true); break;
            case MENU_TEST_THIRD_TASK: task3(true); break;
            default: printf("Неверный выбор!\n");
        }
    }
}