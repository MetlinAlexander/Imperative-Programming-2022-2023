#include "my_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct State{
    char *regs[256];
} State;

//loads string A from I-th register ([idx0] contains its index)
//loads string B from J-th register ([idx1] contains its index)
//then stores concatenation of A and B into I-th register
//BEWARE: [idx0] and [idx1] are allowed to be equal indices
void concat_2( State * state , char * idx0 , char * idx1 ){
    if(state->regs[atoi(idx0)] == NULL || state->regs[atoi(idx1)]==NULL){
        return;
    }
    int len_1 = strlen(state->regs[atoi(idx0)]);
    int len_2 = strlen(state->regs[atoi(idx1)]);
    char* temp = (char*) malloc(sizeof(char)*(len_1+len_2+1));
    for(int i=0; i<len_1; i++){
        temp[i] = state->regs[atoi(idx0)][i];
    }
    for(int i=0; i<=len_2; i++){
        temp[i+len_1] = state->regs[atoi(idx1)][i];
    }
    state->regs[atoi(idx0)] = temp;
}
//extracts sequence of tokens/words separated by underscore character from string [arg]
//puts K –- number of tokens into 0-th register
//puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
void tokenize_1( State * state , char * arg ){
    int k=0;
    int index=0;
    while(arg[index]=='_'){
        index++;
    }
    int temp_index=0;
    char temp[10000];
    while(1){
        if(arg[index]=='\0' && temp_index==0){
            break;
        }
        if(arg[index]=='_' || arg[index]=='\0'){
            k++;
            temp[temp_index]='\0';
            state->regs[k] = (char*) malloc(sizeof(char)*(1+strlen(temp)));
            memcpy(state->regs[k], temp, sizeof(char)*(1+strlen(temp)));
            temp_index=0;
            if(arg[index]=='\0'){
                break;
            }
        }
        while(arg[index]=='_'){
            index++;
        }
        if(arg[index]=='\0') break;
        temp[temp_index] = arg[index];
        temp_index++;
        index++;
    }
    state->regs[0] = (char*) malloc(sizeof(char)*2);
    state->regs[0][0] = (char) (k + '0');
    state->regs[0][1] = '\0';
}