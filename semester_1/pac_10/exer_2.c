#include <stdio.h>
#include <stdlib.h>
typedef struct helper_s {
    int cnt;            //сколько элементов в массиве реально есть
    int cap;            //на сколько элементов выделено место в блоке памяти arr  (capacity)
}helper;

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len
    int n; fscanf(in, "%d", &n); 
    //arr for pointers
    char*** arr = (char***) malloc(1000001*sizeof(char**));
    //arr for space and campasity
    helper* info = (helper*) malloc(1000001*sizeof(helper));
    for(int i=0; i<1000001; i++){
        info[i].cap =0;
        info[i].cnt =0;
    }

    //scan n elements of massiv
    int cur_index, place_in_arr;
    for(int i=0; i<n; i++){
        //scan index
        fscanf(in, "%d ", &cur_index);
        //create massiv for cur inv=dex if this not exist
        if(info[cur_index].cap==0){
            arr[cur_index] = (char**) malloc(2*sizeof(char*));
            info[cur_index].cap = 2;
        }
        //check have we place for new element
        if(info[cur_index].cnt - info[cur_index].cap == 0){
            arr[cur_index] = realloc(arr[cur_index], sizeof(char*)*2*info[cur_index].cap);
            info[cur_index].cap *= 2;
        }
        //scan new elem and put it in array
        place_in_arr = info[cur_index].cnt;
        arr[cur_index][place_in_arr] = (char*) malloc((8) * sizeof(char)); // выделение памяти под массивы
        fscanf(in, "%s", arr[cur_index][place_in_arr]);
        info[cur_index].cnt++;
    }
    //print sort arr
    for(int i=0; i<1000001; i++){
        if(info[i].cnt>0){
            for(int j=0; j<info[i].cnt; j++){
                fprintf(out, "%d %s\n", i, arr[i][j]);//print cur string
                free(arr[i][j]); // clear string memory
            }
            free(arr[i]);
        }
    }
    //free arr
    free(arr);
    free(info);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}