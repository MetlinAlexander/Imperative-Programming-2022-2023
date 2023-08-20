#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// do compare 64bit a and b 
int compare_64 (const void * a, const void * b){
    long long int data1 = *(long long int *)a, data2 = *(long long int *)b;
    if(data1<data2) return -1; // return -1 (or any negative number) if a < b
    else if(data1 == data2) return 0; // return 0 if a == b
    return 1; // return 1 (or any positive number) if a > b
}
// do compare strings a and b 
int compare_strings (const void * a, const void * b){
    const char** data1 = (const char**) a;
    const char** data2 = (const char**) b;
    // printf("%s %s\n", *data1, *data2);
    if(strcmp(*data1, *data2)<0) return -1; // return -1 (or any negative number) if a < b
    else if(strcmp(*data1, *data2)==0) return 0; // return 0 if a == b
    return 1; // return 1 (or any positive number) if a > b
}

//тип указателя на функцию, которую можно передавать как callback
typedef int (* callback )( const void * a, const void * b);

int lower_bound(void* arr, int len, int size_of_each_element, callback comp, void* to_find){
    //if  elem bigger then every element in arr
    if( comp(to_find, (arr+size_of_each_element*(len-1))) == 1){
        return len;
    }
    //if  elem smaller then every element in arr
    if( comp(to_find, arr) <=0){
        return 0;
    }
    //if elem in middle
    int l = 0;
    int h = len;
    while (l < h) {
        int mid =  l + (h - l) / 2;
        if (comp(to_find, (arr+size_of_each_element*mid) )<=0) {
            h = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;

}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //read len of long long int arr
    int n_1; fscanf(in, "%d", &n_1);
    //scan nums
    long long int* arr_num = (long long int*) malloc(n_1*sizeof(long long int));
    for(int i=0; i<n_1; i++){
        fscanf(in, "%lld", &arr_num[i]);
    }
    //scan colovo of words
    int n_2; fscanf(in, "%d", &n_2);
    //scan words
    char** strings = (char**) malloc(n_2*sizeof(char*));
    for(int i=0; i<n_2; i++){
        strings[i] = (char*) malloc(sizeof(char)*32);
        fscanf(in, "%s\n", strings[i]);
    }
    //--------------
    // for(int i=0; i<n_1; i++){
    //     printf("%lld\n", arr_num[i]);
    // }
    // for(int i=0; i<n_2; i++){
    //     printf("%s\n", strings[i]);
    // }
    //--------------
    //sort arrays
    qsort(arr_num, n_1, sizeof(long long int), compare_64);
    qsort(strings, n_2, sizeof(char*), compare_strings);
    // requests
    int req;
    int rez;
    // for 1 arr
    fscanf(in, "%d\n", &req);
    long long int cur_request;
    for(int i=0; i<req; i++){
        fscanf(in, "%lld\n", &cur_request);
        rez = lower_bound(arr_num, n_1, sizeof(long long int), compare_64, &cur_request);
        fprintf(out, "%d\n", rez);
    }
    // for 2 arr
    fscanf(in, "%d\n", &req);
    char* cur_string = (char*) malloc(32*sizeof(char));
    for(int i=0; i<req; i++){
        fscanf(in, "%s\n", cur_string);
        rez = lower_bound(strings, n_2, sizeof(char*), compare_strings, &cur_string);
        fprintf(out, "%d\n", rez);
    }
    //free space
    free(cur_string);
    free(arr_num);
    for(int i=0; i<n_2; i++){
        free(strings[i]);
    }
    free(strings);
    //CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}