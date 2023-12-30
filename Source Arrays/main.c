#include <stdio.h>
#include "util.h"
#include "array_manipulation.h"

/*
Author: Ibrahim Mohamed
Date Created: 4/20/23
Project 3
Purpose: Implementing some basic functions in a separate source file, and compiling with multiple source files to build a program.
*/


void print_array(double *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0)
            printf("{%.3lf", arr[i]);
        else
            printf(",%.3lf", arr[i]);
    }
    printf("}\n");
}

int main() {
    double my_arr[] = {0.5, 1.2, 5.3, 3.9, 4.0};
    int size = sizeof(my_arr) / sizeof(double);
    // {0.500, 1.200, 5.300, 3.900, 4.000}
    print_array(my_arr, size);

    // test array_max()
    double my_max = array_max(my_arr, size);
    // my_max: 5.300000
    printf("my_max: %lf\n", my_max);

    // test array_min()
    double my_min = array_min(my_arr, size);
    // my_min: 0.500000
    printf("my_min: %lf\n", my_min);

    // test array_sum()
    double my_sum = array_sum(my_arr, size);
    // my_sum: 14.900000
    printf("my_sum: %lf\n", my_sum);

    // test array_normalize()
    printf("array normalization:\n");
    array_normalize(my_arr, size);
    // {0.034, 0.081, 0.356, 0.262, 0.268}
    print_array(my_arr, size);
    my_sum = array_sum(my_arr, size);
    // my_sum after normalization: 1.000000
    printf("my_sum after normalization: %lf\n", my_sum);

    // test array_rescale()
    printf("array rescaling:\n");
    array_rescale(my_arr, size);
    // {0.000, 0.146, 1.000, 0.708, 0.729}
    print_array(my_arr, size);
}

