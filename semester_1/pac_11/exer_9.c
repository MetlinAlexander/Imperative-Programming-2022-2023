#include <stdio.h>
#include <stdlib.h>

//struct func for values
typedef struct data_s{
    unsigned long long int m, a, b, c;
}data;


unsigned long long int func ( unsigned long long int state,  data myData) {
    return (state * state * myData.a + state * myData.b + myData.c ) % myData.m;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //read data
    data mydata;
    fscanf(in, "%llu", &mydata.m);
    fscanf(in, "%llu %llu %llu", &mydata.a, &mydata.b, &mydata.c);
    //find cycle
    int i=0, j=1;
    unsigned long long int state_i = 1; 
    unsigned long long int state_j = func(1, mydata);
    while(state_i!=state_j){
        //update i
        i++;
        state_i = func(state_i, mydata);
        //update j
        j+=2;
        state_j = func(state_j, mydata);
        state_j = func(state_j, mydata);
    }
    //find smallest i
    int temp_start =0;
    unsigned long long int temp_state=1;
    while(temp_state!=state_i){
        temp_start++;
        temp_state = func(temp_state, mydata);
    }
    //find smallest j 
    int temp_end = temp_start+1;
    temp_state = func(temp_state, mydata);
    while(temp_state!=state_i){
        temp_end++;
        temp_state = func(temp_state, mydata);
    }
    //find len of cycle
    int difference = temp_end - temp_start;
    //find minimal start and end
    state_i = 1;
    state_j = 1;
    j=0;
    for(i=0; i<difference; i++){
        // printf("%d\n", state_i);
        state_i = func(state_i, mydata);
    }

    while(state_i!=state_j){
        //update i
        i++;
        state_i = func(state_i, mydata);
        //update j
        j++;
        state_j = func(state_j, mydata);
    }
    //print answer
    fprintf(out, "%d %d", j, i);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}