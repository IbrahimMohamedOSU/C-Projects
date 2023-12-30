/*
Author: Ibrahim Mohamed
Date Created: 2/9/2023
Lab 1
Purpose: Write a program that calculates and returns a specified row of Pascal's
triangle
*/

#include <stdio.h>
#include <stdlib.h>

// function definition for void print_array ( int * arr , int size )
void print_array (int *arr, int size) {
int j;
printf("{");
for (j = 0; j < size; j++) {
if (j != size - 1) {
printf("%d, ", arr[j]);
} else {
printf("%d", arr[j]);
}
}
printf("}\n");
}

// function definition for int * getRow_iterative ( int rowIndex , int * returnSize
)
int* getRow_iterative(int rowIndex, int *returnSize) {
int i, k;
int *row = (int *) malloc((rowIndex + 1) * sizeof(int));
for (i = 0; i <= rowIndex; i++) {
row[i] = 1;
for (k = i - 1; k > 0; k--) {
row[k] = row[k] + row[k - 1];
}
}
*returnSize = rowIndex + 1;
return row;
}

// function definition for int * getRow_recursive ( int rowIndex , int * returnSize
)
int *getRow_recursive(int rowIndex, int *returnSize) {
    // allocate memory for an array to save entries of current row
    int *presentRow = (int *)malloc(sizeof(int) * (rowIndex + 1));
    if (rowIndex == 0) { // base case 0
        // set current row to {1}
        presentRow [0] = 1;
        *returnSize = 1;
    } else if (rowIndex == 1) { // base case 1
        // set current row to {1, 1}
        presentRow [0] = 1;
        presentRow [1] = 1;
        *returnSize = 2;
    } else {
        // recursive case
        int *priorRow;
int priorSize;
        // call getRow_recursive() to get previous row of Pascal's Triangle
        priorRow = getRow_recursive(rowIndex - 1, & priorSize);
        // compute entry values of the current row based on previous row
        for (int i = 0; i <= rowIndex; i++) {
            if (i == 0 || i == rowIndex) {
                presentRow [i] = 1;
} else {
                presentRow [i] = priorRow[i - 1] + priorRow[i];
            }
}
        // free allocated memory for previous row
        free(priorRow);
        priorRow = NULL;
        *returnSize = rowIndex + 1;
    }
    return presentRow;
}

int main () {
int rowIndex ;
printf( "input rowIndex : " ) ;
scanf ( "%d" , &rowIndex ) ; // take input from stdin
int size;
int *arr = getRow_iterative ( rowIndex , &size ) ;
print_array ( arr , size ) ;
free( arr ) ; // deallocate memory block
arr = NULL;
arr = getRow_recursive ( rowIndex , &size ) ;
print_array (arr , size ) ;
free( arr ) ; // deallocate memory block
arr = NULL;
return 0; }