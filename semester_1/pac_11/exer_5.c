#include <stdio.h>
#include <stdlib.h>

#include <time.h>
// generate random numbers in range [lower, upper].
int myRand(int lower, int upper){
    
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

//struct func for values
typedef struct data_s{
    unsigned long long int A , B , M , R , S;
}data;

unsigned int hashFunc ( unsigned int x, data mydata) {
    return ((( mydata.A * x + mydata.B) % mydata.M ) % mydata.R) / mydata.S;
}



int main(){
    //generate new seed for random
    srand(time(0));
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //read parametrs
    data mydata;
    fscanf(in, "%llu %llu %llu %llu %llu", &mydata.A, &mydata.B, &mydata.M, &mydata.R, &mydata.S);
    //table
    int table[32][32];
    for(int i=0; i<32; i++){
        for(int j=0; j<32; j++){
            table[i][j] = 0;
        }
    }
    //searsh 
    unsigned int one = 1;
    unsigned int rez;
    unsigned int int_to_find;
    unsigned int count = 0;
    unsigned replace_bit;
    for(unsigned int i=0; i<4294967295-35000; i+=(unsigned int) myRand(20000, 30000)){
        int_to_find = i;
        count++;
        rez= hashFunc(int_to_find, mydata);
        for(int j=0; j<32; j++){
            replace_bit = hashFunc( (int_to_find ^ (one << j)) , mydata);
            for(int k=0; k<32; k++){
                if((  replace_bit & (one<<k)  ) != ( rez & (one<<k) )) {
                    table[j][k] += 1;
                }
            }
        }
    }
    //print table
    int to_print;
    for(int i=0; i<32; i++){
        for(int j=0; j<32; j++){
            to_print = (table[i][j]* 100) / count;
            if(to_print>=100){
                fprintf(out, "%d ", to_print);
            }else 
            if(to_print<=9){
                fprintf(out, "  %d ", to_print);
            }else{
                fprintf(out, " %d ", to_print);
            }
            
        }
        fprintf(out, "\n");
    }
    //CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}