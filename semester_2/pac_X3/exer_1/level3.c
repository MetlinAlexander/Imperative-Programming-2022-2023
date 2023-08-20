#include "myblas.h"
//====== уровень 3 ======
// вычислить матрицу (alpha*A*B + beta*C) и записать её в C
// здесь A –- матрица размера m на k, B –- матрица размера k на n,
// C –- матрица размера m на n
void dgemm(
    int m, int n, int k,
    double alpha, const double *A, const double *B,
    double beta, double *C){
        double temp;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                temp = 0;
                for(int cur=0; cur<k; cur++){
                    temp += A[i*k+cur] * B[cur*n+j];   
                }
                C[n*i+j] = alpha*temp +  C[n*i+j]*beta;
            }
        }

    }