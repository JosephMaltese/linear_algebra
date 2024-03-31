#ifndef FUNCTIONS_H
#define FUNCTIONS_H
// Function prototypes
void generateMatrix(int rows , int cols, double **matrix);
void printMatrix( int rows , int cols, double **matrix ) ;
void addMatrices( int N1 , int M1 , double **A , int N2, int M2, double **B , double **result);
void subtractMatrices(int N1 , int M1 , double **A , int N2 , int M2 , double **B , double **result);
void multiplyMatrices(int N1 , int M1 , double **A , int N2 , int M2 , double **B , double **result);
void solveLinearSystem(int N1 , int M1 , double **A , int N2, int M2 , double **B , double **x);
void deallocateMatrix(double **matrix , int rows );
#endif /* FUNCTIONS_H */