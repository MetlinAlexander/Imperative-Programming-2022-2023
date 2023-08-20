#include <stdio.h>
#include <stdlib.h>

void scanANDprintField(FILE* in, FILE* out){
    fprintf(out, "    "); // print tab
    char temp; 
    fprintf(out, "\""); // open ""
    while(1){
        fread(&temp, sizeof(char), 1, in);
        if( (int) temp ==0){
            break;
        }
        fprintf(out, "%c", temp); // print cur char
    }
    fprintf(out, "\": "); // close "" and print :_
}

void scanString(FILE* in, FILE* out){
    long int len; fread(&len, sizeof(long int), 1, in);
    char temp; 
    fprintf(out, "\""); // open ""
    while(1){
        fread(&temp, sizeof(char), 1, in);
        if( (int) temp ==0){
            break;
        }
        fprintf(out, "%c", temp); // print cur char
    }
    fprintf(out, "\""); // close "" 
}

void scanDouble(FILE* in, FILE* out){
    double temp;
    fread(&temp, sizeof(double), 1, in);
    fprintf(out, "%0.15g", temp);
}

void scanInt32(FILE* in, FILE* out){
    long int temp;
    fread(&temp, sizeof(long int), 1, in);
    fprintf(out, "%ld", temp);
}

void scanInt64(FILE* in, FILE* out){
    long long int temp;
    fread(&temp, sizeof(long long int), 1, in);
    fprintf(out, "%lld", temp);
}

void printNULL(FILE* out){
    fprintf(out, "null");
}

void scanBool(FILE* in, FILE* out){
    char temp;
    fread(&temp, sizeof(char), 1, in);
    if((int) temp == 1)
        fprintf(out, "true", temp);
    else
        fprintf(out, "false", temp);
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "w");
    //scan n
    long int bait_size;
    fread(&bait_size, sizeof(long int), 1, in);
    bait_size -= (long int) sizeof(long int);
    //varibles for scan bson
    char t = (char) 0;
    char prev=0;
    //open bson
    fprintf(out, "{\n");
    //scan bson
    while(bait_size>0){
        //scan type
        fread(&t, sizeof(char), 1, in);
        //print ",\n"
        if((int) t!=0 & (int) prev !=0){
            fprintf(out, ",\n");
        }
        if((int) t==0){ //end of file
            break;
        }
        //scan field
        scanANDprintField(in, out);
        // scan data
        if((int) t==1){ //double
            scanDouble(in, out);
        }else
        if((int) t==2){ //string
            scanString(in, out);
        }else
        if((int) t==8){ //bool
            scanBool(in, out);
        }else
        if((int) t==10){ //null
            printNULL(out);
        }else
        if((int) t==16){ //int32
            scanInt32(in, out);
        }else
        if((int) t==18){ //int64
            scanInt64(in, out);
        }
        prev = t;
    }
    //close bson
    fprintf(out, "\n}");
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
