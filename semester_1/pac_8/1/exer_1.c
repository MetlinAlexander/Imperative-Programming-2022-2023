#include <stdio.h>

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    // FILE *in = fopen("4.in", "rb");
    // FILE *out = fopen("output.txt", "wb");
    //read data
    long int a , b;
    long long int c;
    fread(&a, sizeof(long int), 1, in);
    fread(&b, sizeof(long int), 1, in);
    c = ((long long int) a) + ((long long int) b) ;
    // printf("%ld + %ld = %ld\n", a, b, c);
    if(c>0) c = c/2;
    else if (c<0) c = c/2 - (long int)(c%2!=0);
    // printf("%ld + %ld = %ld", a, b, c);
    fwrite(&c, sizeof(long int), 1, out);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}