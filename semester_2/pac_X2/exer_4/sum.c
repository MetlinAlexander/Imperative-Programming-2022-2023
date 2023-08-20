//выполнить подготовку массива: запускается один раз перед запусками Sum
//здесь arr[0..n) –- это массив A из входного файла
static long long all_sum[100010];
void Init ( const int * arr , int n ){
    all_sum[0] = 0;
    for(int i=1; i<n+1;i++){
        all_sum[i] = all_sum[i-1]+arr[i-1];
    }
}
//найти сумму элементов A на отрезке [l..r)
//использует данные, посчитанные функцией Init
long long Sum ( int l , int r ){
    return all_sum[r] - all_sum[l];
}