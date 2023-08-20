#include <stdio.h>
#include <string.h>
int main(){
    char compiler[10];
    //check compiler
    #if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
        strcpy(compiler, "GCC");
    #elif defined(__TINYC__)
        strcpy(compiler, "TCC");
    #else
        strcpy(compiler, "clang");
    #endif
    // check bitness
    int bitness=0;
    if (sizeof(void*) == 8){
        bitness = 64;
    }
    else{
        bitness = 32;
    }
    //check asserts enable 
    char aser[10];
    #ifdef NDEBUG
        strcpy(aser, "disabled");
    #else
        strcpy(aser, "enabled");
    #endif
    //print answer
    printf("Compiler: %s\n", compiler);
    printf("Bitness: %d\n", bitness);
    printf("Asserts: %s\n", aser);
    return 0;
}