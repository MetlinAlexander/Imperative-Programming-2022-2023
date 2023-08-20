#include <stdio.h>
#include <stdlib.h>
//swap two lines
void swap(double** a, double** b){
    double* temp = *b;
    *b = *a;
    *a = temp;
}
//subtract another line from one multiplied by the coefficient
// a := a - b * t
void sub_two_lines(double* a, double* b, double kf, int len){
    for(int i=0; i<len; i++){
        a[i] = a[i] - b[i]*kf; 
    }
}

// find max in row[start, end] return number of line
int find_max_in_row(double** matrix, int row, int start, int end){
    int index;
    double max_elem;
    //find first not null elements
    for(int i=start; i<end; i++){
        if( (matrix[i][row] > 0.003) || (matrix[i][row] < -0.003)){
            max_elem = matrix[i][row];
            index = i;
            break;
        }
    }
    //find max in row
    for(int i = index; i<end; i++){
        if( (matrix[i][row] > 0.003) || (matrix[i][row] < -0.003) && (matrix[i][row]>max_elem)){
            max_elem = matrix[i][row];
            index = i;
            break;
        }
    }
    return index;
}

//div line to the num
void div_line(double** matrix, int line, double kf, int len){
    for(int i=0; i<len; i++){
        matrix[line][i] /= kf;
    }
}

//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan n (number of equations and variables)
    int n; fscanf(in, "%d", &n);
    //create and scan matrix
    double** matrix = (double**) malloc(sizeof(double*)*n);
    for(int i=0; i<n; i++){
        matrix[i] = (double*) malloc(sizeof(double)*(n+1));
        //scan coefficients
        for(int j=0; j<n+1; j++){
            fscanf(in, "%lf", &matrix[i][j]);
        }
    }

    //solve
    for(int i=0; i<n; i++){
        //find max in row and swap to the diagonal line
        swap(&matrix[i], &matrix[find_max_in_row(matrix, i, i, n)]);
        //div line
        div_line(matrix, i, matrix[i][i], n+1);
        //null lines under diagonal
        for(int j=i+1; j<n; j++){
            sub_two_lines(matrix[j], matrix[i], matrix[j][i], n+1);
        }
        //null lines before diagonal
        for(int j=0; j<i; j++){
            sub_two_lines(matrix[j], matrix[i], matrix[j][i], n+1);
        }

    }

    //free matrix
    for(int i=0; i<n; i++){
        fprintf(out, "%lf\n", matrix[i][n]);
        free(matrix[i]);
    }
    free(matrix);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}