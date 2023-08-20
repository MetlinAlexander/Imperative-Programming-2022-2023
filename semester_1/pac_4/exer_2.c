#include <stdio.h>

void reverse ( char * start , int len ){
    char copy[len+1];
    for(int t = len-1; t>=0; t--){
        copy[t]=start[len-t-1];
    }
    for(int t=0; t<len; t++){
        start[t] = copy[t];
    }
}


int main(){
    int n;
    scanf("%d", &n);
    char mas[100+1];
    int len;
    for(int i=0; i<n; i++){
        scanf("%s", &mas);
        len=0;
        for(int j=0;j<101; j++){
            if(mas[j]=='\0') break;
            len++;
        }
        reverse(mas, len);
        printf("%s\n",mas);
    }
    return 0;
}