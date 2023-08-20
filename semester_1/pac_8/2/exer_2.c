#include <stdio.h>
#include <math.h>
#include <stdlib.h>
char* scan32InChar(FILE* in){
    char* temp = (char*) malloc(4 * sizeof(char));
    for(int i=0; i<4;i++){
        fread(&temp[i], sizeof(char), 1, in);
    }
    return temp;
}

unsigned long int charToBigEndian(char* arr){
    unsigned long int sum = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            sum+= ( (arr[3-i] >> j) & 1) * pow(2, j+i*8);
        }
    }
    return sum;
}

unsigned long int charToLitleEndian(char* arr){
    unsigned long int sum = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            sum+= ( (arr[i] >> j) & 1) * pow(2, j+i*8);
        }
    }
    return sum;
}

int scanLitle32(FILE* in){
    char* list = scan32InChar(in);
    int cur_num = charToLitleEndian(list);
    free(list);
    return cur_num;
}

int scanBig32(FILE* in){
    char* list = scan32InChar(in);
    int cur_num = charToBigEndian(list);
    free(list);
    return cur_num;
}

void writeBig32(int sum, FILE* out){
    char *p = (char*) &sum;
    for(int i=3; i>=0; i--){
        fwrite(&p[i], sizeof(char), 1, out);
    }
}

void writeLitle32(int sum, FILE* out){
    fwrite(&sum, sizeof(long int), 1, out);
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan n
    char* temp_n = scan32InChar(in); // scan first 4 bites to know litle ot big indian
    unsigned long int n;
    int sum = 0; // var for sum
    // try litle indian
    if(charToLitleEndian(temp_n)<=10000){ //litle endian
        n = charToLitleEndian(temp_n); // scan n
        //scan other nums
        for(int i=0; i<n;i++){
            sum+= scanLitle32(in);
        }
        //print answer sum
        writeLitle32(sum, out);
    }
    else{                                 // big indian 
        n = charToBigEndian(temp_n); // scan n
        //scan other nums
        for(int i=0; i<n;i++){
            sum+= scanBig32(in);
        }
        //print answer sum
        writeBig32(sum, out);
    }
    //free temp for n
    free(temp_n);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}