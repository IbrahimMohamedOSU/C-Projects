#include "array_manipulation.h"
#include "util.h"
#include <stdio.h>

#define DEBUG_MODE 1

void array_normalize(double *arr, int size) {
  #ifdef DEBUG_MODE
  printf("enter array_normalize()\n");
  #endif

  double arr_sum = array_sum(arr, size);
  double epsilon = 1e-6;

  if (arr_sum == 0.0) {
    arr_sum = epsilon;
  }

  for (int i = 0; i < size; i++) {
    arr[i] /= (arr_sum + epsilon);
  }
}

void array_rescale(double *arr, int size) {
  #ifdef DEBUG_MODE
  printf("enter array_rescale():\n");
  #endif

  double arr_min = array_min(arr, size);
  double arr_max = array_max(arr, size);

  if (arr_min == arr_max) {
    arr_min = 0.0;
    arr_max = 1.0;
  }

  for (int i = 0; i < size; i++) {
    arr[i] = (arr[i] - arr_min) / (arr_max - arr_min);
  }
}

