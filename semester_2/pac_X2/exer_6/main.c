
#include <stdio.h>

double Function(double x);

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");


    // printf("tets %d %lf\n", f(), Function((double) 0.5));

    int m; fscanf(in, "%d", &m);
    double cur;
    double delta = 0.00000001;
    for(int i=0; i<m; i++){
        fscanf(in, "%lf", &cur);
        if(cur>=0.5){
            fprintf(out, "%lf\n", (Function(cur)-Function(cur-delta)) / delta  );
        }else{
            fprintf(out, "%lf\n", (Function(cur+delta)-Function(cur)) / delta  );
        }
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}