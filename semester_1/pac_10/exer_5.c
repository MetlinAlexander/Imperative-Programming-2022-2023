#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mySin(double x, double eps){
    double ans = x, temp = x;
    for(int n = 3; fabs(temp) > eps; n+=2){
        temp *= (-x*x)/(n*(n-1)); 
        ans += temp;
    }
    return ans;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len
    int n; fscanf(in, "%d", &n);
    //scna an find sin
    double cur;
    double epsilon  = pow(10, -13), t;
    for(int i=0; i<n; i++){
        fscanf(in, "%lf", &cur);
        fprintf(out, "%0.15lf\n", mySin(cur, epsilon));
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}