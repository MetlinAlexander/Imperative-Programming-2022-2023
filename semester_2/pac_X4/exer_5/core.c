#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct State{
    char *regs[256];
} State;
// prints ’ECHO: ’ and all passed strings separated by ’|’
void echo_0(State *state){
    printf("ECHO:\n");
}
void echo_1(State *state, char *arg0){
    printf("ECHO: %s\n", arg0);
}
void echo_2(State *state, char *arg0, char *arg1){
    printf("ECHO: %s|%s\n", arg0, arg1);
}
void echo_3(State *state, char *arg0, char *arg1, char *arg2){
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}
// prints contents of I-th register (it must not be NULL)
//[idx] contains decimal representation of I
void print_1(State *state, char *idx){
    printf("%s\n", state->regs[atoi(idx)]);
}
// prints all non-NULL registers with their values (sorted by register number)
void printregs_0(State *state){
    for(int i=0; i<256; i++){
        if(state->regs[i]){
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
}
// saves a copy of string [what] into I-th register
//[idx] contains decimal representation of I
void store_2(State *state, char *idx, char *what){
    if(state->regs[atoi(idx)]!=NULL){
        free(state->regs[atoi(idx)]);
    }
    state->regs[atoi(idx)] = (char*) malloc(sizeof(char)*(strlen(what)+1));
    memcpy(state->regs[atoi(idx)], what, sizeof(char)*(strlen(what)+1));
}
// copies contents of S-th register into D-th register (S-th register is not NULL)
//[dst] and [src] contain decimal representations of D and S respectively
// BEWARE: [dst] and [src] are allowed to be equal indices
void copy_2(State *state, char *dst, char *src){
    if(atoi(dst)==atoi(src)){
        return;
    }
    store_2(state, dst, state->regs[atoi(src)]);
}
// assigns NULL to I-th register
//[idx] contains decimal representation of I
void clear_1(State *state, char *idx){
    state->regs[atoi(idx)]=NULL;
}