cmake_minimum_required(VERSION 3.28)
project(spbgti C)

set(CMAKE_C_STANDARD 11)

# labwork1
add_executable(labwork1 labwork1/main.c)

# labwork2
add_executable(labwork2 labwork2/main.c)

# labwork3
add_executable(labwork3
        labwork3/main.c
        labwork3/menu.c
        labwork3/menu.h
        labwork3/utils.c
        labwork3/utils.h
        labwork3/io.c
        labwork3/io.h
        labwork3/array.c
        labwork3/array.h
        labwork3/matrix.c
        labwork3/matrix.h
        labwork3/tasks.c
        labwork3/tasks.h
        labwork3/random.c
        labwork3/random.h
)
