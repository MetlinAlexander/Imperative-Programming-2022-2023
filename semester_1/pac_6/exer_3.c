#include <stdio.h>
#include <malloc.h>

int main(){
    //open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan colovo request
    int n; fscanf(in, "%d", &n);
    //variables
    int t, k, l, cur_ind=0, counter;
    char symbol;
    char **arr=NULL;
    arr = (char**) malloc(n * sizeof(char*)); // выделение памяти под указатели на массивы
    //solve zapros
    for(int z=0; z<n; z++){
        //scan type of request
        fscanf(in, "%d", &t);
        //make request
        //printf("--%d--\n", z);
        if(t==0){
            fscanf(in, "%d", &l);//scan len
            arr[cur_ind] = (char*) malloc((l+1) * sizeof(char)); // выделение памяти под массивы
            fscanf(in, "%s", arr[cur_ind]);
            cur_ind++;
        }else
        //1 - delete string
        if(t==1){
            fscanf(in, "%d", &k);
            free(arr[k]);
            arr[k]=NULL;
        }else
        //2 - print string
        if(t==2){
            fscanf(in, "%d", &k);
            fprintf(out, "%s\n", arr[k]);
            //printf("%s\n", arr[k]);
        }else
        //3 - count char in string
        if(t==3){
            counter=0;
            fscanf(in, "%d %c", &k, &symbol);
            for(int i=0; arr[k][i]; i++){
                //printf("%d\n", i);
                if(arr[k][i]==symbol) counter++;
            }
            fprintf(out, "%d\n", counter);
            //printf("%d\n", counter);
        }
    }
    //clean memory
    for(int i=0; i<cur_ind; i++){
        if(arr[i]!=NULL){
            //printf("%d-clean\n", i);
            free(arr[i]);
        }
    }
    free(arr);
    fclose(in);
    fclose(out);
    return 0;
}