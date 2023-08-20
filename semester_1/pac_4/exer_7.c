#include <stdio.h>

int main(){
    //declaration of variables
    char cur_str[1000001];
    int gist[127]={0};
    // scan first string
    gets(cur_str);
    // scan other strings
    do{ 
        for(int i=0; cur_str[i]; i++)
            if ( ((int) cur_str[i]>=32) && ((int) cur_str[i]<=126) )
                gist[(int) cur_str[i]]++;
        //-----
        //gets(cur_str);
        //-----
    }
    while(gets(cur_str)!=NULL);
    //while(cur_str[0]!='\n' && cur_str[0]!='\0');

    // print gistograme
    for(int i = 32; i<=126; i++){
        if (gist[i]!=0){
            printf("%c ", i);
            for(int j = 0; j<gist[i]; j++)
                printf("#");
            printf("\n");
        }
    }
    return 0;
}