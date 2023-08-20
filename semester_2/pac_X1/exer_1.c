#include <stdio.h>
#include <string.h>

//fuction to convert string into number
long long int from_string_to_Num(char* str){
    //find len of number
    int length_of_number =0;
    for(int i=0; str[i]!='\0';i++){
        length_of_number+=1;
    }
    //check if minus
    long long int flag =1;
    int end=0;
    if(str[0]-'-'==0){
        flag=-1;
        end = 1;
    }
    //create num
    long long int num=0, dec=1;
    for(int i=length_of_number-1; i>=end; i--){
        num+= (str[i]-48)*dec;
        dec*=10;
    }
    return num*flag;
}

int main(int argc, char **argv){ // main может принимать эти параметры
    // if no parametrs
    if(argc==1){
        fprintf(stderr, "No parameters specified.");
        return 13;
    }

    //otherwise
    //check if flag -m
    long long int m = 0;
    int start = 1; // where arifmetic operations starts
    if(strcmp("-m", argv[1])==0){ //if -m locate in the start
        m = from_string_to_Num(argv[2]);
        start = 3; // change start
        // printf("%d\n", m);
    }else if(argc>4){
        if(strcmp("-m", argv[4])==0){//if -m locate in the end
            m = from_string_to_Num(argv[5]);
            // printf("%d\n", m);
        }
    }
    //scan and make operations
    // if add
    long long int rez;
    //if without mod
    if(m==0){
        if(strcmp(argv[start], "add")==0){
            rez = (from_string_to_Num(argv[start+1]) + from_string_to_Num(argv[start+2]));
        }else if(strcmp(argv[start], "sub")==0){ // if sub
            rez = (from_string_to_Num(argv[start+1]) - from_string_to_Num(argv[start+2]));
        }else if(strcmp(argv[start], "mul")==0){ // if sub
            rez = (from_string_to_Num(argv[start+1]) * from_string_to_Num(argv[start+2]));
        }
    }else { //if with mod
        if(strcmp(argv[start], "add")==0){
            rez = from_string_to_Num(argv[start+1])%m + from_string_to_Num(argv[start+2]) % m;
        }else if(strcmp(argv[start], "sub")==0){ // if sub
            rez = from_string_to_Num(argv[start+1])%m - from_string_to_Num(argv[start+2]) % m;
        }else if(strcmp(argv[start], "mul")==0){ // if sub
            rez = from_string_to_Num(argv[start+1])%m * from_string_to_Num(argv[start+2])%m  ;
        }
        rez = rez % m;
        if(rez<0){
            rez+=m;
        }
    }
    // mod+
    //print answer
    printf("%lld", rez);

    return 0;                             
}