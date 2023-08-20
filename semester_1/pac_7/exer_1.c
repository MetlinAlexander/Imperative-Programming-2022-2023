#include <stdio.h>
#include <stdlib.h>

typedef struct Elem_s{
    int num; // number of element
    char value[8]; //значение узла
} Elem;

void copy_string(char* first, char* second){
    int i=0;
    while(1){
        first[i] = second[i];
        if(second[i]=='\0') break;
        i++;
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int n; fscanf(in, "%d", &n);
    //massiv of elements
    Elem mass[n]; 
    // scan elements
    for (int i = 0; i < n; i++){
        fscanf(in, "%d %s", &mass[i].num, &mass[i].value);
    }
    //sort massive
    int temp_num; char temp_val[8];
    for(int i=n; i>1; i--){
        for(int j=0; j<i-1; j++){
            if(mass[j].num>mass[j+1].num){
                //change nums
                temp_num = mass[j].num;
                mass[j].num = mass[j+1].num;
                mass[j+1].num = temp_num;
                //change strings
                copy_string(temp_val, mass[j].value);
                copy_string(mass[j].value, mass[j+1].value);
                copy_string(mass[j+1].value, temp_val);
            }
        }
    }
    // print sort list
    for(int i=0; i<n; i++){
        fprintf(out, "%d %s\n", mass[i].num, mass[i].value);
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}