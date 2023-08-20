#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
if (X & (1<<k)) { ... }       //условие верно, если k-ый бит в X равен 1
* int b = (X >> k) & 1;         //возвращает k-ый бит X как число 0 или 1
* X |= (1<<k);                  //устанавливает в k-ый бит X значение 1
* X &= ~(1<<k);
*/

//какой-нибудь целочисленный тип (желательно беззнаковый)
typedef unsigned long long bitword ;
//инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero ( bitword * arr , int num ){
    int len = num/64 + (int)(num%64!=0); // check how many element to null in arr
    //make null all elems
    for(int i=0; i<len; i++){
        arr[i]= (bitword) 0;
    }
}
//возвращает значение idx-ого бита (0 или 1)
int bitsetGet ( const bitword * arr , int idx ){
    int b = (arr[idx/64] >> idx) & ((bitword) 1);
    return b;
}
//устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet ( bitword * arr , int idx , int newval ){
    if(newval==1) arr[idx/64] |= (((bitword) 1) << (idx%64));
    else arr[idx/64] &= ~(((bitword) 1) << (idx%64));
}
//возвращает 1, если среди битов с номерами k
//для left <= k < right есть единичный, и 0 иначе
int bitsetAny ( const bitword * arr , int left , int right ){
    bitword temp;
    //first situations
    if((right/64 - left/64) == 0 ){
        for(int i=left; i<right; i++){
            if(bitsetGet(arr, i)==1 ) {
                return 1;
            }
        }
        return 0;
    }
    //second situations
    // check begin
    for(int i=left; i<(left/64+1)*64;i++){
        // printf("%d ", i);
        if(bitsetGet(arr, i) == 1) {
            return 1;
        }
    }
    // printf("\n");

    //check end

    for(int i=(right/64)*64; i<right;i++){
        // printf("%d ", i);
        if(bitsetGet(arr, i) == 1) {
            return 1;
        }
    }

    //check center
    for(int i=(left/64)+1; i<right/64; i++){
        if(arr[i]!=0) return 1;
    }
    // printf("\n");
    return 0;
}

//установить в val значение всех k-ых битов для left <= k < right
void bitsetSetSeg ( bitword * arr , int left , int right , int newval ){
    // bitword temp;
    //first situations
    if((right/64 - left/64) == 0 ){
        for(int i=left; i<right; i++){
            bitsetSet(arr, i, newval);
        }
        return ;
        // printf("end");
    }
    //second situations
    // check begin
    for(int i=left; i<(left/64+1)*64;i++){
        // printf("%d ", i);
        bitsetSet(arr, i, newval);
    }
    // printf("\n");

    //check end

    for(int i=(right/64)*64; i<right;i++){
        // printf("%d ", i);
        bitsetSet(arr, i, newval);
    }

    //check center
    for(int i=(left/64)+1; i<right/64; i++){
        if(newval==0) arr[i]=0;
        else arr[i]= (-1);
        // printf("%llu\n", arr[i]);
    }
    // printf("\n");
}
//посчитать, сколько битов равно единице на отрезке left <= k < right
int bitsetCount ( const bitword * arr , int left , int right ){
    int count=0;
    //first situations
    if((right/64 - left/64) == 0 ){
        for(int i=left; i<right; i++){
            if(bitsetGet(arr, i)==1) count++;
        }
        return count;
    }
    //second situations
    // check begin
    for(int i=left; i<(left/64+1)*64;i++){
        // printf("%d ", i);
        if(bitsetGet(arr, i)==1) count++;
    }
    // printf("\n");

    //check end

    for(int i=(right/64)*64; i<right;i++){
        // printf("%d ", i);
        if(bitsetGet(arr, i)==1) count++;
    }

    //check center
    for(int i=(left/64)+1; i<right/64; i++){
        count+= __builtin_popcount(arr[i]);
        count+= __builtin_popcount(arr[i]>>32);
    }
    return count;
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int n; fscanf(in, "%d", &n);
    //varibles
    int t, size, index, new_val, left, right, count;
    bitword rez_bit;
    //arr for bitwords
    bitword* arr = (bitword*) malloc(312505*sizeof(bitword));
    // operations
    for(int oper = 0; oper<n; oper++){
        //scan type of opertions
        fscanf(in, "%d", &t); 
        //do operations
        if(t==0){ // bitsetZero
            fscanf(in, "%d", &size);
            // printf("size : %d\n", size);
            bitsetZero(arr, size);
        }else
        if(t==1){ // bitsetGet
            fscanf(in, "%d", &index);
            rez_bit = bitsetGet(arr, index);

            // printf("index %d:", index);
            // printf(" %d\n", rez_bit);

            fprintf(out, "%d\n", rez_bit);
        }else
        if(t==2){ // bitsetSet
            fscanf(in, "%d %d", &index, &new_val);
            bitsetSet(arr, index, new_val);
            // printf("index: %d, value: %d\n", index, bitsetGet(arr, index));
        }else
        if(t==3){ // bitsetSetSeg
            fscanf(in, "%d %d %d", &left, &right, &new_val);
            bitsetSetSeg(arr, left, right, new_val);
            // rez_bit = bitsetAny(arr, left, right);
        }else
        if(t==4){ // bitsetCount
            fscanf(in, "%d %d", &left, &right);
            count = bitsetCount(arr, left, right);
            fprintf(out, "%d\n", count);
        }


    }
    //clear arr
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
