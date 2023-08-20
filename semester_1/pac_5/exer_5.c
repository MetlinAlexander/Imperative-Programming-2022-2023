#include <stdio.h>
#include <malloc.h>
typedef struct LongNum_s{
    int len;      //сколько цифр в числе
    int arr[500]; //массив десятичных цифр числа
} LongNum;

LongNum long_sum(LongNum num_1, LongNum num_2){
    int cur_digit, carry=0, sum, ln=0, distnt;
    if(num_1.len>=num_2.len) distnt = num_1.len;
    else distnt = num_2.len;
    LongNum ans;
    for (int i = 0; i < distnt; i++){
        sum = carry;
        if(num_1.len>i) sum += num_1.arr[i];
        if(num_2.len>i) sum += num_2.arr[i];
        cur_digit = sum%10;
        ans.arr[i]= cur_digit;
        carry=sum/10;
        ln++;
    }
    if(carry!=0){
        ans.arr[ln]=carry;
        ln++;
    }
    ans.len=ln;
    return ans;
}

void print_long(LongNum num){
    for(int i = num.len -1; i>=0; i--){
        printf("%d", num.arr[i]);
    }
    printf("\n");

}


int main()
{   
    //scan variables and allocate memory with malloc
    int n;
    scanf("%d", &n);
    LongNum *fct = malloc(n * sizeof(LongNum));
    LongNum *ukaz = fct;
    int ans = 1;
    if(n<=2) {
        printf("%d", ans);
        return 0;}
    //counting the factorial
    fct[0].len=1, fct[0].arr[0]=1;
    fct[1].len=1, fct[1].arr[0]=1;
    for(int i =2; i<n; i++){
        //make next number
        fct[i]=long_sum(fct[i-1], fct[i-2]);
    }
    //print answer
    print_long(fct[n-1]);
    free(ukaz);
    return 0;
}
