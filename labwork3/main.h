#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

/**
 * @brief Input type for number or array input functions.
 */
typedef enum {
    INT,    /**< Integer number */
    DOUBLE  /**< Floating-point number */
} InputType;

/**
 * @brief Menu options.
 */
typedef enum {
    MENU_EXIT = 0,
    MENU_FIRST_TASK = 1,
    MENU_SECOND_TASK = 2,
    MENU_THIRD_TASK = 3,
    MENU_TEST_FIRST_TASK = 4,
    MENU_TEST_SECOND_TASK = 5,
    MENU_TEST_THIRD_TASK = 6
} Menu;

/**
 * @brief Predicate function type for filtering.
 * @param value Element to check.
 * @return true if the element satisfies the condition, false otherwise.
 */
typedef bool (*Predicate)(int);

/**
 * @brief Displays the main menu.
 */
void showMenu(void);

/**
 * @brief Swaps two double numbers.
 * @param a Pointer to the first number.
 * @param b Pointer to the second number.
 */
void swap(double *a, double *b);

/**
 * @brief Reads a single number (int or double) with input validation.
 * @param type Number type (INT or DOUBLE).
 * @return Entered value as double (can be cast to int if type is INT).
 */
double inputNumber(InputType type);

/**
 * @brief Reads a line of input from the user.
 * @return Pointer to dynamically allocated string. Must be freed by caller.
 */
char* inputLine(void);

/**
 * @brief Reads an array of numbers (int or double) from input.
 * @param type Number type (INT or DOUBLE).
 * @param outCount Pointer to variable to store the number of elements read.
 * @return Pointer to dynamically allocated array. Must be freed by caller.
 */
void* inputArray(InputType type, int* outCount);

/**
 * @brief Initializes the program (locale, srand, prints author info).
 */
void init(void);

/**
 * @brief Frees memory allocated for a matrix.
 * @param matrix Pointer to the matrix (double**).
 * @param N Number of rows.
 */
void freeMatrix(double ***matrix, int N);

/**
 * @brief Reads matrix elements from user input.
 * @param matrix Pointer to matrix (double***), memory is allocated inside function.
 * @param N Number of rows.
 * @param M Number of columns.
 */
void inputMatrix(double ***matrix, int N, int M);

/**
 * @brief Prints an array of int or double numbers.
 * @param arr Pointer to the array.
 * @param size Number of elements.
 * @param type Type of the elements: INPUT_INT or INPUT_DOUBLE.
 */
void printArray(void *arr, int size, InputType type);

/**
 * @brief Prints the matrix to stdout.
 * @param matrix Matrix (double**).
 * @param N Number of rows.
 * @param M Number of columns.
 */
void printMatrix(double **matrix, int N, int M);

/**
 * @brief Performs an in-place cyclic shift of a double array.
 * @param arr Array to shift.
 * @param size Number of elements in the array.
 * @param k Number of positions to shift.
 * @param direction Shift direction: true — right, false — left.
 */
void cyclicShift(double *arr, int size, int k, bool direction);

/**
 * @brief Task 1 function.
 */
void task1(bool test);

/**
 * @brief Task 2 function.
 */
void task2(bool test);

/**
 * @brief Filters elements of an integer array according to a predicate.
 *
 * @param src Pointer to the source array.
 * @param size Number of elements in the source array.
 * @param pred Pointer to a predicate function (returns true/false).
 * @param dst Pointer to the destination array (must be allocated enough memory).
 * @return Number of elements in the filtered array.
 */
int filter(const int *src, int size, Predicate pred, int *dst);

/**
 * @brief Task 3 function.
 */
void task3(bool test);

/**
 * @brief Main program loop (menu).
 */
void run(void);

void shutdown(void);

#endif // MAIN_H