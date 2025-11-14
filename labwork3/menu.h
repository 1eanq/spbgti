#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_EXIT = 0,
    MENU_FIRST_TASK = 1,
    MENU_SECOND_TASK = 2,
    MENU_THIRD_TASK = 3,
    MENU_TEST_FIRST_TASK = 4,
    MENU_TEST_SECOND_TASK = 5,
    MENU_TEST_THIRD_TASK = 6
} Menu;

void runMenu(void);

#endif