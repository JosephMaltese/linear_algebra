#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// CODE: include necessary library(s)

void deallocateMatrix(double **matrix , int rows ) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to generate a random matrix
void generateMatrix(int rows, int cols, double **matrix) {
    // CODE: Generate random numbers between -10 and 10
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for matrix[%d]\n", i);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < cols; j++) {
            // Generate a random number between -10 and 10 (inclusive)
            matrix[i][j] = (20*((double)rand() / RAND_MAX)) - 10; // store the random number in the current position of the matrix
        }
    }
}

// Function to print a matrix
void printMatrix(int rows, int cols, double **matrix) {
    // loop through rows and columns of matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // print the value at the current position of the matrix.
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}
// Function to add two matrices
void addMatrices(int N1, int M1, double **A, int N2, int M2, double **B, double **result) {
    // CODE: check for the condition 
    // ensure the rows and columns of both matrices are equal
    if (N1 != N2 || M1 != M2) {
        printf("Addition is not defined for matrices of these dimensions.\n");
        return;
    }

    // loop through all the rows and values of the resultant matrix, and set the value at the current position equal
    // to the sum of the values at the corresponding position in matrix A and B 
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < M1; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    } 

}

// CODE: do the same for subtractMatrices, multiplyMatrices, and solveLinearSystem functions


void subtractMatrices(int N1, int M1, double **A, int N2, int M2, double **B, double **result) {
    // CODE: check for the condition 
    // rows and columns of A and B must be equal
    if (N1 != N2 || M1 != M2) {
        printf("Subtraction is not defined for matrices of these dimensions.\n");
        return;
    }

    // loop through all the rows and values of the resultant matrix, and set the value at the current position equal
    // to the difference of the values at the corresponding position in matrix A and B 
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < M1; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    } 
}


void multiplyMatrices(int N1, int M1, double **A, int N2, int M2, double **B, double **result) {
    // Check if multiplication is defined
    // The number of columns in A must be equal to the number of rows in B
    if (M1 != N2) {
        printf("Multiplication is not defined for matrices of these dimensions.\n");
        return;
    }
    
    // loop through every column and row of the resultant matrix (which has the same number of rows as A and same
    // number of columns as B)
    // Then traverse across the ith row of A and down the jth column of B and multiply their values.
    // the corresponding value in the resultant matrix will be equal to the sum of each product.
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < M2; j++) {
            double sum = 0.0;
            // loop from 0 to M1, which is the number of cols in A and the number of rows in A.
            // since i is constant in A and j is constant in B, this allows us to iterate across the ith row in A
            // from left to right and iterate down the jth column of B
            for (int k = 0; k < M1; k++) {
                sum += (A[i][k] * B[k][j]);
            }
            result[i][j] = sum;
        }
    }
}



void solveLinearSystem(int N1, int M1, double **A, int N2, int M2, double **B, double **x) {
    // Check to ensure that the number of rows in matrix A and B are the same and that B is a vector (1 col)
    if (N1 != N2 || M2 != 1) {
        printf("The given matrices are not compatible to solve.\n");
        return;
    }
    // ensure that A is square
    if (N1 != M1) {
        printf("Matrix A must be square.\n");
        return;
    }

    // this code block puts the matrix into row-echelon form
    // loops through all the rows of A
    for (int i = 0; i < N1; i++) {
        // loops through all the columns of A
        for (int j = 0; j< M1; j++) {
            
            // check if at a pivot position
            if (i == j) {
                // if one of the pivot positions in A has a zero, cannot solve.
                if (A[i][j] == 0) {
                    printf("A pivot equals 0. Cannot solve this case.\n");
                    return;
                }
                // if the pivot value is not equal to 1, set it to 1 by dividing all values in the row by the pivot
                // value
                if (A[i][j] != 1) {
                    // the divFactor is just the value at the pivot position
                    double divFactor = A[i][j];
                    // loop through each element in current row of A
                    for (int k = 0; k < M1; k++) {
                        A[i][k] = A[i][k] / divFactor;
                        
                    }
                    // Also divide the element in the corresponding row in B by the div factor, as operations are 
                    // performed on the augmented matrix
                    B[i][0] = B[i][0] / divFactor;
                }
            
            }
            // Check if below pivot position. If so, must perform operations so that all values below the pivot are 0
            // This is to get the matrix into upper triangular form
            if (i>j) {
                // Don't do anything if value at current position is zero.
                if (A[i][j] == 0) {
                    continue;
                }
                // if the value at current position is not zero, add a constant multiple of the row containing the pivot
                // to it to get it equal to 0
                else {
                    // the constant multiple is the value at the current position divided by the value at the pivot.
                    // Adding this to the current value will cancel out, resulting in 0.
                    double factor = A[i][j] / A[j][j];

                    // loop through each element in the current row and subtract the corresponding value in the 
                    // pivot row multiplied by the constant multiple from it
                    for (int k = 0; k < M1; k++) {
                        A[i][k] = A[i][k] - factor * A[j][k];
                    }
                    // do the same with the corresponding elements in B, as row operations must be performed
                    // on the augmented matrix
                    B[i][0] = B[i][0] - factor * B[j][0];
                }
            }
        }
    }

    // set the last x value equal to the last value in the reduced B matrix.
    x[N1-1][0] = B[N1-1][0];

    // backwards substitution
    // Loop through rows of A in reverse order, starting from second last row.
    for (int i = (N1 - 2); i >= 0; i-- ) {
        double sum = 0;

        // loop through each element to the right of the pivot and accumulate them in a sum.
        // Also multiply the value by its corresponding x value in the equation as more x values are solved.
        for (int j = i + 1; j < M1; j++) {
            sum += A[i][j]*x[j][0];
        }
        // The x value in the current row is equal to the b value of the current row minus the sum.
        x[i][0] = (B[i][0] - sum);  

    }
    
}