#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int a_1, a_2, b_1, b_2, c_1, c_2;
    fscanf(in, "%d %d %d %d %d %d", &a_1, &a_2, &b_1, &b_2, &c_1, &c_2);
    fclose(in);
    if (( a_1 >= b_1) && (a_2 >= b_2))
    {
        int x_1 = a_1-b_1;
        int y_1 = a_2;
        int x_2 = a_2-b_2;
        int y_2 = a_1;
        if ( ((x_1>=c_1) && (y_1>=c_2)) || ((x_1>=c_2) && (y_1>=c_1))){
            fprintf(out, "YES");
            fclose(out);
            return 0;    
        }
        if ( ((x_2>=c_1) && (y_2>=c_2)) || ((x_2>=c_2) && (y_2>=c_1))){
            fprintf(out, "YES");
            fclose(out);
            return 0;
        }
    }
    if (( a_1 >= b_2) && (a_2 >= b_1))
    {
        int x_3 = a_1-b_2;
        int y_3 = a_2;
        int x_4 = a_2-b_1;
        int y_4 = a_1;
        if ( ((x_3>=c_1) && (y_3>=c_2)) || ((x_3>=c_2) && (y_3>=c_1))){
            fprintf(out, "YES");
            fclose(out);
            return 0;    
        }
        if ( ((x_4>=c_1) && (y_4>=c_2)) || ((x_4>=c_2) && (y_4>=c_1))){
            fprintf(out, "YES");
            fclose(out);
            return 0;
        }
    }

    fprintf(out, "NO");
    fclose(out);
    return 0;
}