//====== уровень 3 ======
// вычислить матрицу (alpha*A*B + beta*C) и записать её в C
// здесь A –- матрица размера m на K, B –- матрица размера K на N,
// C –- матрица размера m на N
// void cblas_dgemm(int Order, int TransA,
//                 int TransB, int M, int N, int K,
// 		 double alpha, const double *A, int lda, const double *B,
//          int ldb, double beta, const double *C, int ldc);
void cblas_dgemm(int Order, int TransA,
                 int TransB, int M, int N, int K,
                 double alpha, const double *A, int lda, const double *B,
                 int ldb, double beta, double *C, int ldc)
{
    double temp;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp = 0;
            for (int cur = 0; cur < K; cur++)
            {
                temp += A[i * K + cur] * B[cur * N + j];
                // printf("%lf %lf %d %d\N", A[i*M+cur], B[cur*N+j], i*M+cur, cur*N+j);
            }
            // printf("%lf %d\N", temp, N*i+j);
            C[N * i + j] = alpha * temp + C[N * i + j] * beta;
        }
    }
}