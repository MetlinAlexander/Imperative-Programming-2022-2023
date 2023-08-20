#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* scanChar(FILE* in, int len){
    char* cur_char = (char*) malloc((len+1)*sizeof(char));
    char temp;
    for(int i=0; i<len; i++){
        fread(&temp, sizeof(char), 1, in);
        if((int) temp == 1){
            cur_char[i] = '1';
        }else{
            cur_char[i] = '0';
        }
    }
    cur_char[len] = '\0';
    return cur_char;
}

void writeBait(FILE* out, const char* bait){
    int temp = 0;
    //make decem number
    for(int i=7; i>=0; i--){
        if(bait[i] == '1'){
            temp += pow(2, i);
        }
    }
    //write to the output.txt
    char a = (char) temp;
    fwrite(&a, sizeof(char), 1, out);
}



int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan n
    long int n;
    fread(&n, sizeof(long int), 1, in);
    //scan alphabet
    long int l;
    char** alphabet = (char**) malloc(sizeof(char*)*n);
    for(int i=0; i<n; i++){
        fread(&l, sizeof(long int), 1, in);
        alphabet[i]= scanChar(in, l);
    }
    //scan text to print
    long int m;
    fread(&m, sizeof(long int), 1, in);
    short int cur_symbol;
    //vars for bait
    char to_write[9];
    int len_to_write=0;
    for(int i=0; i<m;i++){
        fread(&cur_symbol, sizeof(short int), 1, in);
        for(int j=0; alphabet[cur_symbol][j]!='\0'; j++){
            if(len_to_write>=8){
                //write new bait
                to_write[len_to_write] = '\0';
                len_to_write = 0;
                //write to the output.txt
                writeBait(out, to_write);
            }
            //write cur bit
            to_write[len_to_write] = alphabet[cur_symbol][j];
            len_to_write++;
        }
    }
    //write last bait
    for(int i=0; ; i++){
        if(len_to_write>=8){
            //write new bait
            to_write[len_to_write] = '\0';
            len_to_write = 0;
            //write to the output.txt
            writeBait(out, to_write);
            break;
        }
        //write cur bit
        to_write[len_to_write] = '0';
        len_to_write++;
    }
    //clear space
    for(int i=0; i<n; i++){
        free(alphabet[i]);
    }
    free(alphabet);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}