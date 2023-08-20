#include "integerset.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// do compare a and b
int compare (const void * a, const void * b){
    int data1 = *(int *)a, data2 = *(int *)b;
    if(data1<data2) return -1; // return -1 (or any negative number) if a < b
    else if(data1 == data2) return 0; // return 0 if a == b
    return 1; // return 1 (or any positive number) if a > b
}


IntegerSet* CreateSet(int* arr, int size){
    if(size==0){ 
        IntegerSet* cur_set = (IntegerSet*) malloc(sizeof(IntegerSet));
        cur_set->set = NULL;
        cur_set->size_set = size;
        return cur_set;
    }
    //create set
    IntegerSet* cur_set = (IntegerSet*) malloc(sizeof(IntegerSet));
    cur_set->set = (int*) malloc(sizeof(int)*size);
    cur_set->size_set = size;
    //copy arr
    memcpy(cur_set->set, arr, sizeof(int)*size);
    //sort arr
    qsort(cur_set->set, size, sizeof(int), compare); 
    //check for equal elements
    for(int i=0; i<size-1; i++){
        if(cur_set->set[i]==cur_set->set[i+1]){
            free(cur_set->set);
            free(cur_set);
            return NULL;
        }
    }
    return cur_set;
}

int IsInSet(IntegerSet* cur_set, int elem){
    //if null set was given
    if(cur_set==NULL){
        return 0;
    }
    if(cur_set->size_set==0){
        return 0;
    }
    //find elem in set with bin search
    int l=0, r=cur_set->size_set-1, mid;
    while (l <= r) {
        mid = l + (r - l) / 2;
 
        // Check if elem in set
        if (cur_set->set[mid] == elem)
            return 1;
 
        // If elem greater, ignore left half
        if (cur_set->set[mid] < elem)
            l = mid + 1;
 
        // If elem is smaller, ignore right half
        else
            r = mid - 1;
    }
 
    // if elem not in set
    return 0;

}