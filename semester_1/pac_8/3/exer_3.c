#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

void writeLitle32(int sum, FILE* out){
    fwrite(&sum, sizeof(long int), 1, out);
}
#pragma pack(push, 1) 
typedef struct MyFile_s{
    char name[21]; // 0-20 name of file
    unsigned long long int size; // 21-28 size of file
    char bit_directory; // 29 directory bit
    unsigned long long int time_made; // 30-37 time of made file
    unsigned long long int time_change; // 38-45 last time change file
    char bit_hiden; // 46 is file hiden
}MyFile;
#pragma pack(pop)

void print_file(MyFile cur_file){
    printf("name: %s\nsize: %llu\ndirect:%d\nmade: %llu\nchange: %llu\nhiden: %d\n", cur_file.name, cur_file.size, cur_file.bit_directory, cur_file.time_made, cur_file.time_change, cur_file.bit_hiden);
    printf("-----------------------\n");
}

void copy_string(char* first, char* second){
    for(int i=0; i<21; i++){
        first[i] = second[i];
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan n a b
    int n;
    unsigned long long int a, b;
    fread(&n, sizeof(long int), 1, in);
    fread(&a, sizeof(unsigned long long int), 1, in);
    fread(&b, sizeof(unsigned long long int), 1, in);
    // printf("n = %d; a = %llu; b = %llu\n", n, a, b);
    //array for files
    MyFile* arr = (MyFile*) malloc(n*sizeof(MyFile));
    //array for possible files
    MyFile* good_files = (MyFile*) malloc(n*sizeof(MyFile));
    int real_len = 0;
    // scan n files
    for(int i=0; i<n; i++){
        //read file
        fread(&arr[i], sizeof(MyFile), 1, in);
        //check if this possible file
        if((arr[i].bit_directory!=1 & arr[i].bit_hiden!=1) & (arr[i].time_made>=a & arr[i].time_change<=b)){
            good_files[real_len] = arr[i]; // add possible file
            real_len++; // update_len
            // print_file(good_files[real_len-1]);
        }
    }
    //sort files by names with bubble sort
    MyFile temp_val;
    for(int i=real_len-1; i>0; i--){
        // print_file(good_files[i]);
        for(int j=0; j<i; j++){
            // printf("%d and %d\n", j, j+1);
            if(strcmp(good_files[j].name, good_files[j+1].name) >0){
                //change files
                temp_val = good_files[j];
                good_files[j] = good_files[j+1];
                good_files[j+1] = temp_val;
            }
        }
    }
    //print sort files
    fwrite(good_files, sizeof(MyFile), real_len, out);
    //clear arr
    free(arr);
    free(good_files);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}