#include <stdio.h>

typedef struct DateTime_s
{
    int year, month, day;
    int hours, minutes, seconds;
} DateTime;

DateTime min(const DateTime *arr, int cnt)
{
    int mn = 0;
    for(int i=1; i<cnt; i++){
        // compare year
        if(arr[i].year>arr[mn].year) 
            continue;
        else if (arr[i].year<arr[mn].year){
            mn =i;
            continue;
        }
        // compare month
        else if(arr[i].month>arr[mn].month) 
            continue;
        else if (arr[i].month<arr[mn].month){
            mn = i;
            continue;
        }
        // compare days
        else if(arr[i].day>arr[mn].day) 
            continue;
        else if (arr[i].day<arr[mn].day){
            mn = i;
            continue;
        }
        // compare hours
        else if(arr[i].hours>arr[mn].hours) 
            continue;
        else if (arr[i].hours<arr[mn].hours){
            mn = i;
            continue;
        }
        // compare minutes
        else if(arr[i].minutes>arr[mn].minutes) 
            continue;
        else if (arr[i].minutes<arr[mn].minutes){
            mn = i;
            continue;
        }
        // compare seconds
        else if(arr[i].seconds>arr[mn].seconds) 
            continue;
        else if (arr[i].seconds<arr[mn].seconds){
            mn = i;
            continue;
        }
    }
    return arr[mn];
}

int main()
{
    //declaration of variables
    int n;
    scanf("%d", &n);
    DateTime a[n];
    // scan dates
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d %d %d", &a[i].year, &a[i].month, &a[i].day, &a[i].hours, &a[i].minutes, &a[i].seconds);
    }
    // search minimal date
    DateTime *ukaz = a;
    DateTime answer;
    answer = min(ukaz, n);
    printf("%d %d %d %d %d %d", answer.year, answer.month, answer.day, answer.hours, answer.minutes, answer.seconds);
    return 0;
}


/*
5
2018 8 12 23 44 13
2018 9 1 9 0 0
2019 1 1 0 0 0
2018 2 13 13 1 7
2018 8 26 8 20 11
*/