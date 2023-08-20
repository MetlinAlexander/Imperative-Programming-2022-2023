#include <stdio.h>

int readTime ( char * iStr , int * oHours , int * oMinutes , int * oSeconds ){
    int dv_cn=0, h, m, s;
    //check correct
    for(int i=0; iStr[i]; i++){
        if(iStr[i]=='|'){
            *oHours=-1;
            if(oMinutes!=NULL) *oMinutes=-1;
            if(oMinutes!=NULL && oSeconds!=NULL) *oSeconds=-1;
            return 0;
        }
        if(iStr[i]==':') dv_cn++;
    }
    if(dv_cn==1){
        sscanf(iStr, "%d:%d", &h, &m);
        if(h<=23 && h>=0 && m>=0 && m<=59){
            *oHours=h;
            if(oMinutes!=NULL) *oMinutes=m;
        }
        else{
            *oHours=-1;
            if(oMinutes!=NULL) *oMinutes=-1;
            if(oMinutes!=NULL && oSeconds!=NULL) *oSeconds=-1;
            return 0;
        }
    }
    else if(dv_cn==2){
        sscanf(iStr, "%d:%d:%d", &h, &m, &s);
        if(h<=23 && h>=0 && m>=0 && m<=59 && s>=0 && s<=59){
            *oHours=h;
            if(oMinutes!=NULL) *oMinutes=m;
            if(oMinutes!=NULL && oSeconds!=NULL) *oSeconds=s;
        }
        else{
            *oHours=-1;
            if(oMinutes!=NULL) *oMinutes=-1;
            if(oMinutes!=NULL && oSeconds!=NULL) *oSeconds=-1;
            return 0;
        }
        
    }
    // scan h, m, s
    
    return 1;
}

int main(){
    //declaration of variables
    char time_str[100];
    int rez, h_u=0, m_u=0, s_u=0;
    // scan string
    gets(time_str);
    //printf("%s\n", time_str);
    // time test
    rez = readTime(time_str, &h_u, &m_u,&s_u);
    printf("%d %d %d %d\n", rez, h_u, m_u, s_u);
    rez = readTime(time_str, &h_u, &m_u, NULL);
    printf("%d %d %d\n", rez, h_u, m_u);
    rez = readTime(time_str, &h_u, NULL, NULL);
    printf("%d %d", rez, h_u);
    
    return 0;
}