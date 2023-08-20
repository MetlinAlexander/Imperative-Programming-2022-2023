#include <stdio.h>

char * concat ( char * pref , char * suff ){
    //contacenate pref+suff
    while(*suff)
   {
      *pref = *suff;
      suff++;
      pref++;
   }
    return pref;
}

int main(){
    //declaration of variables
    int n;
    scanf("%d", &n);
    char add_string[100+1];
    char ans[1000001];
    // scan first string
    scanf("%s", &ans);
    char* ukaz = &ans[0];
    while(*ukaz){
        ++ukaz;
    }
    // scan other strings and concenate
    for(int i=0; i<n-1; i++){
        scanf("%s", &add_string);
        ukaz = concat(ukaz, add_string);
    }
    // print answer
    printf("%s", ans);
    return 0;
}