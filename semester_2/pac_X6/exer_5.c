#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int INF = 2100000000;
//  c(u, v) --- пропускная способность трубы из u в v (0 если трубы нет)
//   f(u, v) --- величина потока по трубе из u в v
int** c;
int** f;
int* parent;
char* mark;
int* queue;
int cur=0, put=0;
int answer_flow=0;
typedef struct Edge_s{
    int from, to;
}Edge;
Edge* answer;
int ans_count=0;

void max_flow(int s, int t, int n){
    for(int i=0; i<n; i++){
        parent[i]=-1;
    }
    mark = (char*) malloc(sizeof(char)*(n));
    queue = (int*) malloc(sizeof(int)*(100000));
    int u, v;
    int CP;
    int x, y;
    while(1){
        for(int i=0; i<n; i++){
            mark[i]='f';
        }
        cur=0, put=0;
        mark[s] = 't';
        queue[put] = s;
        put++;
       
        while (cur<put){
            //извлекаем вершину из начала очереди
            u = queue[cur];
            cur++;
            for(v=0; v<n; v++){
                if( c[u][v] - f[u][v] > 0){// проверяем cf(uv) -- остаточную проп. спос-сть
                    if (mark[v]=='f'){
                        mark[v] = 't';
                        queue[put] = v;
                        put++;
                        parent[v] = u;
                    }  
                }  
            }
        }
        if (mark[t]=='f'){ // нет дополняющего пути
            break;
        }
        // part 2: how much?
        CP = 1;
        // part 3: push flow
        x = t;
        while( x != s){               // восстанавливаем путь P второй раз
            y = parent[x];
            f[y][x] += CP;
            f[x][y] -= CP;               // не забываем поменять поток по обратному ребру!
            x = y;
        }
        answer_flow += CP;
    }
    free(mark);
}




int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int a, b, m; fscanf(in, "%d %d %d", &a, &b, &m);
    //scan edges
    Edge* connections = (Edge*) malloc(sizeof(Edge)*m); 
    for(int i=0; i<m; i++){
        fscanf(in, "%d %d", &connections[i].from, &connections[i].to);
    }
    // init
    int vertex_num = 1+a+b+1;
    c = (int**) malloc(sizeof(int*) * (vertex_num));
    f = (int**) malloc(sizeof(int*) * (vertex_num));
    for(int i=0; i<vertex_num; i++){
        c[i] = (int*) malloc(sizeof(int)*(vertex_num));
        f[i] = (int*) malloc(sizeof(int)*(vertex_num));
        for(int j=0; j<vertex_num; j++){
            c[i][j] =0;
            f[i][j] =0;
        }
    }
    parent = (int*) malloc(sizeof(int)*(vertex_num));
//create graph
    //connect all students with start
    //and all exersices with finish
    //and them together
    int student, exer;
    for(int i=0; i<m; i++){
        student = connections[i].from;
        exer = connections[i].to;
        c[0][student] = 1;
        c[student][exer+a] = 1;
        c[exer+a][vertex_num-1] = 1;
    }
    //find max flow
    max_flow(0, vertex_num-1, vertex_num);
    fprintf(out, "%d\n", answer_flow);
    for(int i=1; i<a+1; i++){
        if(f[0][i]==1){
            for(int j=a+1; j<vertex_num-1;j++){
                if(f[i][j]==1){
                    exer = j;
                    break;
                }
            }
            fprintf(out, "%d %d\n", i, exer-a);
        }
    }
    //free
    for(int i=0; i<vertex_num; i++){
        free(c[i]);
        free(f[i]);
    }
    free(c);
    free(f);
    free(parent);
    free(connections);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}