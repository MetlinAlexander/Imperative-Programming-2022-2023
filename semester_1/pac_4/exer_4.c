#include <stdio.h>

int calcLetters ( char * iStr , int * oLowerCnt , int * oUpperCnt , int * oDigitsCnt ){
    int ln=0;
    *oLowerCnt=0;
    *oUpperCnt=0;
    *oDigitsCnt=0;
    for(int i=0; iStr[i]; i++){
        ln++;
        if( (97<= (int) iStr[i]) && ((int) iStr[i]<= 122))
            (*oLowerCnt)++;
        else if( (65<= (int) iStr[i]) && ((int) iStr[i]<= 90))
            (*oUpperCnt)++;
        else if( (48<= (int) iStr[i]) && ((int) iStr[i]<= 57))
            (*oDigitsCnt)++;
    }
    return ln;
}

int main(){
     //declaration of variables
    char cur[101];
    int i=1;
    int len, lowerCnt , upperCnt , digitsCnt;
    // scan first string
    gets(cur);
    // scan other strings
    do{ 
        len = calcLetters(cur, &lowerCnt, &upperCnt, &digitsCnt);
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, len, (lowerCnt+upperCnt), lowerCnt, upperCnt, digitsCnt);
        //update info for next string
        i++;
    }
    while(gets(cur)!=NULL);
    return 0;
}