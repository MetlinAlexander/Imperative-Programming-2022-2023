#include <stdio.h>
// Euclidean algorithm
int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a%b);
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan how many tests
    int t; fscanf(in, "%d", &t);
    // scan every test and print answer
    int a, b;
    for(int i=0; i<t; i++){
        //scan cur a and b
        fscanf(in, "%d %d", &a, &b);
        //print answer
        fprintf(out, "%d\n", gcd(a, b));
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}