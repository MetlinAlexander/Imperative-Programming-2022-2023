#include <stdio.h>
#include <stdlib.h>


//fast pow
long long int fast_pow(long long int x, long long int p, long long int mod){
    long long int r=1;
    while(p>0){
        if(p%2==1){
            r = (r*x)%mod;
        }
        x= (x*x)%mod;
        p /=2;
    }
    return r%mod;
}

//find inverse elem
long long int inverse(long long int num, long long int mod){
    return fast_pow(num, mod-2, mod);
}


//swap two lines
void swap(long long int** a, long long int** b){
    long long int* temp = *b;
    *b = *a;
    *a = temp;
}
//subtract another line from one multiplied by the coefficient
// a := a - b * t
void sub_two_lines(long long int* a, long long int* b, long long int kf, int len, long long int mod){
    for(int i=0; i<len; i++){
        a[i] = a[i] - (b[i]*kf)%mod ; 
        a[i] = ((a[i]%mod)+mod)%mod;
    }
}

// find first not null elmenet and return index of line, if not < then return -1
int find_not_Null(long long int** matrix, int row, int start, int end){
    int index = -1;
    for(int i=start; i<end; i++){
        if(matrix[i][row]!=0){
            index=i;
            break;
        }
    }
    return index;
}

//div line to the num
void div_line(long long int** matrix, int line, long long int kf, int len, long long int mod){
    for(int i=0; i<len; i++){
        matrix[line][i] = ( matrix[line][i] * inverse(kf, mod)) %mod;
    }
}

//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan : n (number of variables) 
    // k ( number of equations)
    // p (mod)
    int n, k; long long int p; fscanf(in, "%d %d %lld", &n, &k, &p);

    //create and scan matrix
    long long int** matrix = (long long int**) malloc(sizeof(long long int*)*k);
    for(int i=0; i<k; i++){
        matrix[i] = (long long int*) malloc(sizeof(long long int)*(n+1));
        for(int j=0; j<n+1; j++){
            fscanf(in, "%lld", &matrix[i][j]);
        }
    }

    //solve
    //make stairs matrix
    int cur_row = 0;
    int cur_line = 0;
    int cur_max_in_row;
    int free_vars = 0;
    while(1){
        // printf("%d %d %d\n", free_vars, cur_line, cur_row);
        //check if this end of matrix
        //check rows
        if(cur_row>=n){
            break;
        }
        //check lines
        if(cur_line>=k){
            free_vars += (n - cur_row);
            break;
        }
        //find max in row and swap to the diagonal line 
        cur_max_in_row = find_not_Null(matrix, cur_row, cur_line, k);
        //if every thing is null
        if(cur_max_in_row == -1){
            free_vars +=1;
            cur_row+=1;
            continue;
        }
        //otherwise
        swap(&matrix[cur_line], &matrix[cur_max_in_row]);
        
        //div line
        div_line(matrix, cur_line, matrix[cur_line][cur_row], n+1, p);

        //null lines under diagonal
        for(int j=cur_line+1; j<k; j++){
            sub_two_lines(matrix[j], matrix[cur_line], matrix[j][cur_row], n+1, p);
        }
        //null lines before diagonal
        for(int j=0; j<cur_line; j++){
            sub_two_lines(matrix[j], matrix[cur_line], matrix[j][cur_line], n+1, p);
        }
        //update row and line
        cur_line++;
        cur_row++;
    }
    //check if no solves
    for(int i=cur_line; i<k; i++){
        if(matrix[i][n]!=0){
            fprintf(out, "%d", 0);
            // printf("0");
            return 0;
        }
    }
    // if more than 1 solves 
    if(free_vars>0){
        fprintf(out, "%d", fast_pow(p, free_vars, 1000000007));
        return 0;
    }

    //if only 1 solutions
    fprintf(out, "%d\n", 1);

    //free matrix
    for(int i=0; i<cur_line; i++){
        fprintf(out, "%lld\n", matrix[i][n]);
        free(matrix[i]);
    }
    //coninue free matrix
    for(int i=cur_line; i<k; i++){
        free(matrix[i]);
    }
    free(matrix);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}