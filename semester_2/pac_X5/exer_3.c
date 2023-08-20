#include <stdio.h>
#include <stdlib.h>

typedef struct cell_s{
    int x;
    int y;
}cell;

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int m, n; fscanf(in, "%d %d\n", &m, &n);
    // m - height, n- width
    char** labirint = (char**) malloc(sizeof(char*)*(m));
    cell start; start.x =-1; start.y = -1;
    cell finish; finish.x = -1; start.y = -1;
    for(int i=0; i<m;i++){
        labirint[i] = (char*) malloc(sizeof(char)*(n+1));
        for(int j=0; j<n+1;j++){
            fscanf(in, "%c", &labirint[i][j]);
            if(labirint[i][j]=='S'){
                start.x = i;
                start.y = j;
            }
            if(labirint[i][j]=='F'){
                finish.x = i;
                finish.y = j;
            }
        }
        labirint[i][n] = '\0';
    }
    //if they didnt give us start and finish
    if( (start.x == -1) || (start.y == -1) || (finish.x == -1) || (finish.y == -1)){
        fprintf(out, "-1");
        //free
        for(int i=0; i<m; i++){
            free(labirint[i]);
        }
        free(labirint);
        return 0;
    }
    //find shortest way with bfs
    //solve
    int** length = (int**) malloc(sizeof(int*)*(m));
    for(int i=0; i<m; i++){
        length[i] = (int*) malloc(sizeof(int)*n);
        for(int j=0; j<n;j++){
            length[i][j] = -1;
        }
    }
    cell* queue = (cell*) malloc(sizeof(cell)*(n*m));
    int cur=0, put=0;
    //bfs
    length[start.x][start.y] = 0; 
    queue[0].x = start.x;
    queue[0].y = start.y;
    put = 1;
    cell u, v;
    while(put-cur>0){
        //извлекаем вершину из начала очереди
        u = queue[cur];
        cur++;
        
        if(u.x-1>=0){
            if(labirint[u.x-1][u.y]=='.'){
                queue[put].x = u.x-1;
                queue[put].y = u.y;
                put++;
                length[u.x-1][u.y] = length[u.x][u.y]+1;
                labirint[u.x-1][u.y] = 'v';
            }
            //if this finish
            if(labirint[u.x-1][u.y]=='F'){
                length[u.x-1][u.y] = length[u.x][u.y]+1;
                break;
            }
        }
        if(u.x+1<m){
            if(labirint[u.x+1][u.y]=='.'){
                queue[put].x = u.x+1;
                queue[put].y = u.y;
                put++;
                length[u.x+1][u.y] = length[u.x][u.y]+1;
                labirint[u.x+1][u.y] = 'v';
            }
            //if this finish
            if(labirint[u.x+1][u.y]=='F'){
                length[u.x+1][u.y] = length[u.x][u.y]+1;
                break;
            }
        }
        if(u.y-1>=0){
            if(labirint[u.x][u.y-1]=='.'){
                queue[put].x = u.x;
                queue[put].y = u.y-1;
                put++;
                length[u.x][u.y-1] = length[u.x][u.y]+1;
                labirint[u.x][u.y-1] = 'v';
            }
            //if this finish
            if(labirint[u.x][u.y-1]=='F'){
                length[u.x][u.y-1] = length[u.x][u.y]+1;
                break;
            }
        }
        if(u.y+1<n){
            if(labirint[u.x][u.y+1]=='.'){
                queue[put].x = u.x;
                queue[put].y = u.y+1;
                put++;
                length[u.x][u.y+1] = length[u.x][u.y]+1;
                labirint[u.x][u.y+1]='v';
            }
            //if this finish
            if(labirint[u.x][u.y+1]=='F'){
                length[u.x][u.y+1] = length[u.x][u.y]+1;
                break;
            }
        }
    }

    //print answer
    fprintf(out, "%d\n", length[finish.x][finish.y]);
    //free
    for(int i=0; i<m; i++){
        free(labirint[i]);
        free(length[i]);
    }
    free(labirint);
    free(length);
    free(queue);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}