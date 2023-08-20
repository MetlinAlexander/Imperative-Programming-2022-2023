#include <stdio.h>

typedef struct LongNum_s{
    int len;      //сколько цифр в числе
    int arr[3000]; //массив десятичных цифр числа
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

void scan_long(LongNum *ans){
    int ln =0, digit, i=0;
    char cur;
    int temp[3000];
    while(1){
        scanf("%c", &cur);
        if(cur=='\n' || cur==' ' || cur=='\0') break;
        digit = (int) cur -48;
        temp[i] = digit;
        i++;
        ln++;
    }
    ans->len = ln;
    for(int i=0; i<ln; i++){
        ans->arr[i] = temp[ln-1-i];
    }
}

void print_long(LongNum num){
    for(int i = num.len -1; i>=0; i--){
        printf("%d", num.arr[i]);
    }
    printf("\n");

}

LongNum long_mult(LongNum num_1, LongNum num_2){
    LongNum cur;
    LongNum rez;
    cur.len=0;
    rez.len=1, rez.arr[0]=0;
    int carry, mlp, digit;
    //check zero
    if((num_1.len==1 && num_1.arr[0]==0) || (num_2.len==1 && num_2.arr[0]==0)){
        rez.arr[0]=0;
        rez.len=1;
        return rez;
    }
    //multiply
    for(int i=0; i< num_2.len; i++){
        carry=0;
        for(int z=0; z<i; z++){
            cur.arr[z]=0;
            cur.len++;
        }
        for(int j=i; j<num_1.len+i; j++){
            mlp = num_1.arr[j-i] * num_2.arr[i] + carry;
            digit = mlp%10;
            carry = mlp/10;
            cur.arr[j]=digit;
            cur.len++;
        }
        if(carry!=0){
            cur.arr[cur.len]=carry;
            cur.len++;
        }
        rez = long_sum(rez, cur);
        // clean cur
        for(int c =0; c<cur.len; c++){
            cur.arr[0]=0;
        }
        cur.len=0;
    }
    return rez;
}

int main(){
    LongNum test_1, test_2;
    scan_long(&test_1);
    scan_long(&test_2);
    LongNum rez;
    rez = long_mult(test_1, test_2);
    print_long(rez);
    return 0;
}