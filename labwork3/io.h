#ifndef IO_H
#define IO_H

typedef enum { INT, DOUBLE } InputType;

char* inputLine(void);
double inputNumber(InputType type);
void* inputArray(InputType type, int *count);

#endif