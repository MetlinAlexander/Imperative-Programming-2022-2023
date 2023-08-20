#include <stdio.h>
#include <stdlib.h>


void matrix_DFS(char** matrix , int i, int j) {
    matrix[i][j] = '#';        //отмечаем, что мы посетили v
    //запускаем DFS только для ранее непосещённых вершин
    if(matrix[i-1][j]==' '){
        matrix_DFS(matrix, i-1, j);
    }
    if(matrix[i+1][j]==' '){
        matrix_DFS(matrix, i+1, j);
    }
    if(matrix[i][j-1]==' '){
        matrix_DFS(matrix, i, j-1);
    }
    if(matrix[i][j+1]==' '){
        matrix_DFS(matrix, i, j+1);
    }

}



int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n; fscanf(in, "%d\n", &n); 

    char** labirint = (char**) malloc(sizeof(char*)*(n+1));
    labirint[0] = (char*) malloc(sizeof(char)*(n+1));
    labirint[0][n] = '\0';
    for(int i=0; i<n;i++){
        labirint[0][i] = '*';
    }
    char temp;
    for(int i=1; i<n+1; i++){
        labirint[i] = (char*) malloc(sizeof(char)*(n+1));
        fgets(labirint[i], n+1, in);
        fscanf(in, "%c", &temp);
    }
    //solve
    for(int i=0; i<n; i++){
        printf("%s\n", labirint[i]);
    }
    // Алгоритм поиска компонент связности:
    int c = -1; // how many rooms
    //изначально все вершины белые
    for(int i=1; i<n+1;i++){//перебираем все вершины (в любом порядке)
        for(int j=0; j<n;j++){
            if(labirint[i][j]==' '){ //когда видим белую вершину, запускаем из неё DFS
                matrix_DFS(labirint, i, j);
                c++; // increase room counter
            }        
        }
    }
    if(c==-1) c=0;
    fprintf(out, "%d", c);
    //free
    for(int i=0; i<n+1;i++){
        free(labirint[i]);
    }
    free(labirint);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}