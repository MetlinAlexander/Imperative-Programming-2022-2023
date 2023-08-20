#include <stdio.h>
#include <math.h>
int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    char bit;
    int cur = 0;
    int length = 0;
    fscanf(in, "%d", &n );
    fscanf(in, "%c", &bit);
    for(int i = 0; i<n;i++){
        fscanf(in, "%c", &bit);
        if(bit=='1') cur += (int) pow(2, length);
        length++;
        if(length == 8) {
            fprintf(out, "%d ", cur);
            length=0;
            cur=0;
        }
    }
    if (length>0) fprintf(out, "%d", cur);
    return 0;
}