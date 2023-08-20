#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double function(double* coef, double t, double l){
    double rez=0;
    // rez = coef[0] + coef[1]*(t-l) + coef[2] * pow((t-l), 2) + coef[3]*pow((t-l), 3);
    // rez = coef[1] + coef[2]*2*t - 2 * coef[2] *l + 3*t*t*coef[3] - 6*l*t*coef[3] + 3* l*l*coef[3];
    rez= coef[1] + coef[2]*2*(t-l) + coef[3]*3*(t-l)*(t-l);
    return rez; 
}

double integral(double* x, double* y, double* z, double t, double l){
    // double delta = 0.00000001;
    double rez=0;
    // rez += pow( (function(x, t, l) - function(x, t+delta, l))/ delta , 2);
    // rez += pow( (function(y, t, l) - function(y, t+delta, l))/ delta , 2);
    // rez += pow( (function(z, t, l) - function(z, t+delta, l))/ delta , 2);
    // rez += pow( function(x, t, l) , 2);
    // rez += pow( function(y, t, l), 2);
    // rez += pow( function(z, t, l) , 2);
    rez += function(x, t, l) *  function(x, t, l);
    rez += function(y, t, l) *  function(y, t, l);
    rez += function(z, t, l) *  function(z, t, l);

    return sqrt(rez);
}

double simpson(double* x, double* y, double* z, double a, double b, double l){
    double rez = 0;
    rez+= integral(x, y, z, a, l);
    rez+= 4 * integral(x, y, z, (a+b)/2, l);
    rez += integral(x, y, z, b, l);
    rez = rez * ((b-a)/6);
    return rez;

}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    //scan number of spans
    int n; fscanf(in, "%d", &n);
    // printf("n=%d\n", n);
    //scan every span
    double l, r;
    double x[4];
    double y[4];
    double z[4];
    double length = 0, temp=0, step;
    double h;
    for(int i=0; i<n; i++){
        //scan cur [l, r]
        fscanf(in, "%lf %lf", &l, &r);
        // printf("[%lf, %lf]\n", l, r);
        //scan values for x
        fscanf(in, "%lf %lf %lf %lf", &x[0], &x[1], &x[2], &x[3]);
        // printf("x : %lf %lf %lf %lf\n", x[0], x[1], x[2], x[3]);
        //scan values for x
        fscanf(in, "%lf %lf %lf %lf", &y[0], &y[1], &y[2], &y[3]);
        // printf("y : %lf %lf %lf %lf\n", y[0], y[1], y[2], y[3]);
        //scan values for x
        fscanf(in, "%lf %lf %lf %lf", &z[0], &z[1], &z[2], &z[3]);
        // printf("z : %lf %lf %lf %lf\n", z[0], z[1], z[2], z[3]);
        //solve
        step = (r-l)/100;
        temp = 0;
        for(int j=1; j<101; j++){

            length += simpson(x, y, z, l + (j - 1) * step, l+step * j, l);
            // length += simpson(x, y, z, l + temp, l+step +temp);
            temp+=step;
        }
        
        // length += simpson(x, y, z, l, r);
        // temp += sqrt( pow(function(x, l, l))  )
        // h = ()/3
        // for(int j=0; j<100; j++){

        // }
    }
    // 3.54886798803189495999
    //print answer
    // printf("%0.20g", length);
    fprintf(out, "%0.20g", length);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}