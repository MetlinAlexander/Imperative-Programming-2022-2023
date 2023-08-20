#include <stdlib.h>
#include <stdio.h>

// initializes members of [vec] structure for empty array
void CONCAT(NAME, _init)(NAME *vec){
    vec->n = 0;
    vec->camp = 2;
    vec->arr = (TYPE*) malloc(sizeof(TYPE)*vec->camp);
}

// makes array [vec] empty and frees its array buffer [vec->arr]
// note: this function can be called many times
void CONCAT(NAME, _destroy)(NAME *vec){
    if(vec->arr != NULL){
        vec->n = 0;
        vec->camp = 0;
        free(vec->arr);
        vec->arr = NULL;
    }
}

// adds element [value] to the end of array [vec]
// returns index of the added element
int CONCAT(NAME, _push)(NAME *vec, TYPE value){
    //if arr wasnt allocate
    if(vec->camp == 0){
        CONCAT(NAME, _init)(vec);
    }
    //check if enough space in arr
    if(vec->n == vec->camp){
        //otherwise
        vec->camp *= 2;
        vec->arr = realloc(vec->arr, (vec->camp)*sizeof(TYPE));
    }
    vec->arr[vec->n] = value;
    vec->n += 1;
    return vec->n - 1;
}

// removes the last element from array [vec]
// returns removed element
TYPE CONCAT(NAME, _pop)(NAME *vec){
    vec->n -= 1;
    TYPE temp = vec->arr[vec->n];
    return temp;
}

// ensures that array [vec] has enough storage for [capacity] elements
// note: address of elements surely won’t change before [vec->n] exceeds capacity
void CONCAT(NAME, _reserve)(NAME *vec, int capacity){
    //if arr wasnt allocate
    if(vec->arr == NULL){
        CONCAT(NAME, _init)(vec);
    }
    //if now in array enough space
    if(capacity<=vec->camp){
        return ;
    }
    //otherwise
    vec->camp = capacity*2;
    vec->arr = realloc(vec->arr, vec->camp *sizeof(TYPE));
}

// changes number of elements in array [vec] to [newCnt]
// if the number increases, new elements get value [fill]
// if the number decreases, some elements at the end are removed
void CONCAT(NAME, _resize)(NAME *vec, int newCnt, TYPE fill){
    //if arr wasnt allocate
    if(vec->arr == NULL){
        CONCAT(NAME, _init)(vec);
    }
    //check if enough space in arr
    if(newCnt>vec->camp){
        vec->camp = newCnt*2;
        vec->arr = realloc(vec->arr, (vec->camp)*sizeof(TYPE));
    }
    //if newCnt > cur_size
    if(newCnt>vec->n){
        for(int i=vec->n; i<newCnt; i++){
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
    //if newCnt == cursize nothing happend
}

// inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
// in-between elements [vec->arr[where-1]] and [vec->arr[where]]
// note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void CONCAT(NAME, _insert)(NAME *vec, int where, TYPE *arr, int num){
    if(num==0){
        return ;
    }
    //if arr wasnt allocate
    if(vec->arr == NULL){
        CONCAT(NAME, _init)(vec);
    }
    //check if enough space in arr
    if(vec->n + num > vec->camp){
        vec->camp = (vec->n + num) * 2;
        vec->arr = realloc(vec->arr, (vec->camp)*sizeof(TYPE));
    }
    // relocate some data
    for(int i=vec->n-1; i>=where; i--){
        vec->arr[i + num] = vec->arr[i];
    }
    int extra_index = 0;
    for(int i = where; i<where+num; i++){
        vec->arr[i] = arr[extra_index];
        extra_index+=1;
    }
    vec->n += num;
    return ;

}

// removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
// all the elements starting from [where+num]-th are shifted left by [num] positions
void CONCAT(NAME, _erase)(NAME *vec, int where, int num){
    //if arr wasnt allocate
    if(vec->arr == NULL){
        CONCAT(NAME, _init)(vec);
    }
    //relocate some data
    for(int i =where+num; i<vec->n; i++){
        vec->arr[i-num] = vec->arr[i];
    }
    vec->n -= num;
    return ;
}