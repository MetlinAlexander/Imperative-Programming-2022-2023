#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//дизьюнкция двух битовых массивов
void bitsetOR ( bitword * change_arr , const bitword* not_change_arr, int num ){
    int len = num/64 + (int)(num%64!=0); // check how many element to OR in arr
    //make OR
    for(int i=0; i<len; i++){
        change_arr[i] |= not_change_arr[i];
    }
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan size
    int n; fscanf(in, "%d\n", &n); 
    //arr for bitwords
    bitword** set = (bitword**) malloc(n*sizeof(bitword*));
    //scan matrix
    char temp_bit;
    for(int i=0; i<n; i++){
        set[i] = (bitword*) malloc((n/64 + 1)*sizeof(bitword));
        bitsetZero(set[i], n/64 +1);
        for(int j=0; j<n; j++){
            fscanf(in, "%c", &temp_bit);
            if(i==j){ // заполняем диагональ единицами
                bitsetSet(set[i], j, 1);
            }else
            if(temp_bit=='1'){
                bitsetSet(set[i], j, 1);
            }else
            if(temp_bit=='0'){
                bitsetSet(set[i], j, 0);
            }
        }
        fscanf(in, "%c", &temp_bit);
    }
    //find all ways
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            if(bitsetGet(set[i], k)==1){
                bitsetOR(set[i], set[k], n);
            }
        }
    }
    //print answer and clean memory
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            fprintf(out, "%d", bitsetGet(set[i], j));
        }
        free(set[i]);
        fprintf(out, "\n");
    }
    free(set);
    
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}