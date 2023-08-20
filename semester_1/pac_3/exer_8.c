#include <stdio.h>
#include <ctype.h>
#include <math.h>
int main()
{   
    // scan input
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int p, q;
    fscanf(in, "%d %d", &p, &q);
    char pr;
    fscanf(in, "%c", &pr);
    int length = 0;
    char a[40] = {'-'};
    while (1)
    {   
        a[length] = ' ';
        fscanf(in, "%c", &a[length]);
        if(a[length] == '\n' || a[length] == '\0') break;
        length++;
    }
    // make decem number
    int decem = 0;
    int digit;
    char cur;
    for(int i=length-1; i>=0; i--){
        cur = a[i];
        if(isdigit(cur)){
            digit = (int) cur - 48;
            decem += digit * pow(p, length-i-1);
        }
        else{
            digit = (int) cur - 87;
            decem += digit * pow(p, length-i-1);
        }
    }
    // make from decem -  q number
    char new_num[40];
    length = 0;
    char alpabet[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while (decem>0){
        cur = decem%q;
        new_num[length] = alpabet[cur];
        length++;
        decem= decem/q;
    };
    // print answer
    for(int i = length-1; i>=0; i--){
        if(isdigit(new_num[i])){
            digit = (int) new_num[i] - 48;
            fprintf(out, "%d", digit);
        }
        else{
            fprintf(out, "%c", new_num[i]);
        }
        //printf("%c", (char)*new_num);
    }
    return 0;
}