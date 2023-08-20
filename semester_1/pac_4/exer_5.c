#include <stdio.h>

char * string_analysis(char* cur, int* len, int* cnUpper, char* word){
    //stringanalysis
    *len=0;
    *cnUpper=0;
    while((*cur!='.') && (*cur!=',') && (*cur!=';') && (*cur!=':') && *cur){
        if( (65<= (int) *cur) && ((int) *cur<= 90))
            (*cnUpper)++;
        *word=*cur;
        (*len)++;
        word++;
        cur++;
    }
    *word='\0';
    return cur;
}

char * pass_symbols (char * cur){
    //pass_symbols
    while(((*cur=='.') || (*cur==',') || (*cur==';') || (*cur==':')) && *cur)
        cur++;
    return cur;
}

int main(){
    //declaration of variables
    char cur_string[1000001];
    char ans[1000001];
    int len, upperCnt;
    // scan string
    gets(ans);
    char* ukaz = &ans[0];
    // string analysis
    while(*ukaz)
   {
    ukaz = pass_symbols(ukaz);
    ukaz = string_analysis(ukaz, &len, &upperCnt, cur_string);
    if(cur_string[0])printf("%d/%d %s\n", upperCnt, len, cur_string);
    //ukaz++;
   }
    
    return 0;
}