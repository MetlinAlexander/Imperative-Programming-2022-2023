#include <stdio.h>

//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //parse file
    int word_before = 0;
    char cur_char;
    while( 1){ // parse until EOF
        // printf("%c", cur_char);
        cur_char = fgetc(in);
        if(cur_char == EOF) break;
        //if this space
        if(cur_char=='\n'){
            break;
        }
        if(cur_char == ' '){
            continue;
        }
        // if this ""
        if(cur_char == '"'){
            if(word_before){
                fprintf(out, "\n");
            }else{
                word_before = 1;
            }
            fprintf(out, "[");
            while(1){
                cur_char = fgetc(in);
                if(cur_char == EOF | cur_char == '\n') break;
                if(cur_char=='"') 
                    break;
                fprintf(out, "%c", cur_char);
            }
            fprintf(out, "]");
            continue;
        }
        //if this start of arguments
        if(word_before){
            fprintf(out, "\n");
        }else{
            word_before = 1;
        }
        fprintf(out, "[%c", cur_char);
        while(1){
            cur_char = fgetc(in);
            if(cur_char == EOF | cur_char == '\n') break;
            if(cur_char == ' ') 
                break;
            fprintf(out, "%c", cur_char);
        }
        fprintf(out, "]");
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}