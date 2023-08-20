extern int n;
long long Sum ( int l , int r );
//находит самый длинный отрезок с началом в l и суммой не более sum
//возвращает правый край искомого отрезка
int Query ( int l , long long sum ){
    // search with upper bound
    int mid;

    int left = l;
    int right = n+1;

    while (left<right-1){
        mid = left + (right - left) /2;
        if( Sum(l, mid) <= sum ){
                left = mid;
        }else{
            right = mid;
        }
    }

    return left;
    
}
