#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"
#include <stdbool.h>
// CODE: include necessary library(s)

int main(int argc, char *argv[]) {
    // generate a seed for random number generation based on time
    srand(time(NULL));

    // Check if the number of arguments is correct
    if (argc < 6 || argc > 7) {
        printf("Usage: %s nrows_A ncols_A nrows_B ncols_B <operation> [print]\n", argv[0]);
        return 1;
    }

    // Define the numbers of rows and columns in matrix A and B based on the command line arguments given
    int rowsA = atoi(argv[1]);
    int colsA = atoi(argv[2]);

    int rowsB = atoi(argv[3]);
    int colsB = atoi(argv[4]);

    // CODE: Generate random matrices A with size N1*M1 and B with size N2*M2
    double **matrixA = (double **)malloc(rowsA * sizeof(double *));
    if (matrixA == NULL) {
            fprintf(stderr, "Memory allocation failed for matrixA\n");
            exit(EXIT_FAILURE);
        }

    double **matrixB = (double **)malloc(rowsB * sizeof(double *));
    if (matrixB == NULL) {
            fprintf(stderr, "Memory allocation failed for matrixB\n");
            exit(EXIT_FAILURE);
        }
    // Call generate matrix function to assign random values from -10 to 10 to matrix A 

    generateMatrix(rowsA, colsA, matrixA); 
    generateMatrix(rowsB, colsB, matrixB);

    bool print = false;
    // checks if 7 arguments are given (including name of object file)
    if (argc == 7) {
        // if 7 arguments are given and the last one is print, then print the matrices and relevant results.
        if (strcmp(argv[6], "print") == 0) {
            print = true;
        }
    }

    // if the user selected print, display matrix A and B in the terminal
    if (print == true) {
        printf("Matrix A:\n");
        printMatrix(rowsA, colsA, matrixA);
        printf("\n");
        printf("Matrix B:\n");
        
        printMatrix(rowsB, colsB, matrixB);
        printf("\n");
    }
    clock_t start, end;
    double cpu_time_taken;

    // If the command line arugment in index position 5 is add, add matrix A and B
    if (strcmp(argv[5], "add") == 0) {
        // define result matrix to store final answer of addition. Dimensions are the same as matrix A, because
        // adding matrices requires A and B to be the same size.
        double **addResult = (double **)malloc(rowsA*sizeof(double *)); //[rowsA][colsA];

        for (int i = 0; i < rowsA;i++) {
            addResult[i] = (double *)malloc(colsA*sizeof(double));
        }

        // Check that the condition is met for addition 
        if (rowsA == rowsB && colsA == colsB) {
            start = clock();
            addMatrices(rowsA, colsA, matrixA, rowsB, colsB, matrixB, addResult);
            end = clock();
            
            cpu_time_taken = ((double) (end-start)) / CLOCKS_PER_SEC;
            printf("Time taken: %f seconds\n", cpu_time_taken);
            // if the user selected print, then print the result of the addition.
            if (print == true) {
                printf("Result of A + B:\n");
                printMatrix(rowsA,colsA, addResult);
            }
        }
        else {
            printf("Addition is not defined for matrices of these dimensions.\n");
            return 0;
        }

        deallocateMatrix(addResult,rowsA);
        

        
    }
    // If the command line arugment in index position 5 is subtract, subtract matrix A and B
    else if (strcmp(argv[5], "subtract") == 0) {
        // define result matrix to store final answer of subtraction. Dimensions are the same as matrix A, because
        // subtracting matrices requires A and B to be the same size.
        double **subtractResult = (double **)malloc(rowsA*sizeof(double *));          //[rowsA][colsA];

        for (int i = 0; i < rowsA; i++) {
            subtractResult[i] = (double *)malloc(colsA*sizeof(double));
        }

        // Check if condition is met
        if (rowsA == rowsB && colsA == colsB ) {
            // call subtraction function
            start = clock();
            subtractMatrices(rowsA,colsA,matrixA,rowsB,colsB,matrixB, subtractResult);
            end = clock();

            cpu_time_taken = ((double) (end-start)) / CLOCKS_PER_SEC;
            printf("Time taken: %f seconds\n", cpu_time_taken);

            // if the user selected print, print the subtraction answer.
            if (print == true) {
                printf("Result of A - B:\n");
                printMatrix(rowsA,colsA, subtractResult);
            }
        }
        else {

            printf("Subtraction is not defined for matrices of these dimensions.\n");
            return 0;
        }

        deallocateMatrix(subtractResult,rowsA);

    }
    // If the command line arugment in index position 5 is multiply, multiply matrix A and B
    else if (strcmp(argv[5], "multiply") == 0) {
        // define matrix to store solution of multiplication of matrix A and B. The product of two matrices
        // have the same number of rows as A and the same number of columns as B
        double **multiplicationResult = (double **)malloc(rowsA*sizeof(double *));      //[rowsA][colsB];

        for (int i = 0; i < rowsA; i++) {
            multiplicationResult[i] = (double *)malloc(colsB*sizeof(double));
        }

        if (colsA == rowsB) {
            start = clock();
            multiplyMatrices(rowsA, colsA, matrixA, rowsB, colsB, matrixB, multiplicationResult);
            end = clock();

            cpu_time_taken = ((double) (end-start)) / CLOCKS_PER_SEC;
            printf("Time taken: %f seconds\n", cpu_time_taken);

            // if the user selected print, print the multiplication answer.
            if (print == true) {
                printf("Result of A * B:\n");
                printMatrix(rowsA,colsB, multiplicationResult);

            }
        }
        else {
            printf("Multiplication is not defined for matrices of these dimensions.\n");
            return 0;
        }
        deallocateMatrix(multiplicationResult,rowsA);
       
    }
    // If the command line arugment in index position 5 is solve, solve the system of linear equations pertaining
    // to matrix A and B
    else if (strcmp(argv[5], "solve") == 0) {
        
        // Check if condition is met
        if (rowsA != colsA) {
            printf("Matrix A must be square to solve.\n");
            return 0;
        }
        if (colsB != 1 || rowsB != rowsA) {
            printf("Matrix B must be a vector with the same number of rows as matrix A.\n");
            return 0;
        }
        // define the matrix to store the solution to the system of linear equations. It should be a vector, so its
        // column size is 1, and it has the same number of rows as matrix A and B.
        double **solveResult = (double **)malloc(rowsA*sizeof(double *));                 //[rowsA][1];

        for (int i = 0; i < rowsA; i++) {
            solveResult[i] = (double *)malloc(sizeof(double));
        }

        start = clock();
        solveLinearSystem(rowsA, colsA, matrixA, rowsB, colsB, matrixB, solveResult);
        end = clock();

        cpu_time_taken = ((double) (end-start)) / CLOCKS_PER_SEC;
        printf("Time taken: %f seconds\n", cpu_time_taken);


        // if the user selected print, print the answer to the system of linear equations.
        if (print == true) {
            printf("Result of x=B/A:\n");
            printMatrix(rowsA,1, solveResult);
        }
        deallocateMatrix(solveResult,rowsA);
    }
    // If any other command-line argument is given in index position 5, the operation is unrecognized.
    else {
        printf("Operation undefined.\n");
        return 0;
    }

    deallocateMatrix(matrixA,rowsA);
    deallocateMatrix(matrixB,rowsB);


    return 0;

}