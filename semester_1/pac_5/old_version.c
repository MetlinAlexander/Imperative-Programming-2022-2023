#include <stdio.h>
#include <malloc.h>
typedef struct LongNum_s{
    int len;      //сколько цифр в числе
    int arr[500]; //массив десятичных цифр числа
} LongNum;
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
    //printf("%d\n", fct[1].len);
    int cur_digit, carry=0, cur, ln;
    for(int i =2; i<n; i++){
        //make next number
        ln=0;
        carry=0;
        for (int j = 0; j < fct[i-1].len; j++){
            if(fct[i-2].len>j) cur = fct[i-1].arr[j] + fct[i-2].arr[j] + carry;
            else cur = fct[i-1].arr[j] + carry;
            cur_digit = cur%10;
            fct[i].arr[j]= cur_digit;
            carry=cur/10;
            ln++;
        }
        if(carry!=0){
            fct[i].arr[ln]=carry;
            ln++;
        }
        // update len
        fct[i].len=ln; 
    }
    //print answer
    ln = fct[n-1].len;
    for(int i = ln-1; i>=0; i--){
        printf("%d", fct[n-1].arr[i]);
    }
    free(ukaz);
    return 0;
}

/*
LongNum long_sum(LongNum num_1, LongNum num_2){
    int cur_digit, carry=0, sum, ln=0;
    LongNum ans;
    if(num_1.len>=num_2.len){
        for (int i = 0; i < num_1.len; i++){
            if(num_1.len>i) sum = num_1.arr[i] + num_2.arr[i] + carry;
            else sum = num_1.arr[i] + carry;
            cur_digit = sum%10;
            ans.arr[i]= cur_digit;
            carry=sum/10;
            ln++;
        }
    }
    
    else{
        for (int i = 0; i < num_2.len; i++){
            if(num_2.len>i) sum = num_1.arr[i] + num_2.arr[i] + carry;
            else sum = num_2.arr[i] + carry;
            cur_digit = sum%10;
            ans.arr[i]= cur_digit;
            carry=sum/10;
            ln++;
        }
    }
    if(carry!=0){
        ans.arr[ln]=carry;
        ln++;
    }
    ans.len=ln;
    return ans;
}
    */