/*
10
0/1 xor 8000000000000000
1/1 xor 0000000000000000
1/1 xor 8000000000000000
1/1 xor 3ff0000000000000
1/1 xor 7ff0000000000000
1/1 xor 0010000000000000
1/1 xor 000a000000000000
3/7 xor 8000000000000000
3/7 xor 8b0abc0000000000
3/7 xor 000000000000d000
*/
#include <stdio.h>
// typedef long long int bitword;
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int n; fscanf(in, "%d", &n);
    //vars
    int p, q;
    long long m, l_ans;
    double chastnoe;
    long long *p_chast = (long long*) &chastnoe;
    double *p_answer = (double*) &l_ans;
    //scan requests
    for(int i=0; i<n; i++){
        fscanf(in, "%d/%d xor %llx", &p, &q, &m);
        chastnoe = (double) p / (double) q;
        l_ans =(*p_chast ^ m);
        p_answer = (double*) &l_ans;
        fprintf(out, "%0.15g\n", *p_answer);
        // answer = (double) l_ans;
        // printf("%d - %0.15g;  p=%d, q=%d ; answer: %0.15g = %lld \n", i, chastnoe, p, q, *p_answer);
    }

    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}