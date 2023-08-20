#include "pack.h"
#include <stdarg.h> 
// #include <stdio.h>
// Packs specified arguments into specified "buffer" as binary data.

// The arguments are passed in printf-like fashion.
// Format string consists only of the following pieces:
//   %d  --- next argument is signed 32-bit int
//   %lf --- next argument is 64-bit floating point number
//   %s  --- next argument is null-terminated string

// All the arguments are copied into buffer in the correct order.
// For %d and %lf, 4 and 8 bytes respectively are copied into the buffer.
// For %s, the whole string including null-terminated byte is copied into buffer.

// The return value is the total number of bytes written to the buffer.
// Since caller does not know how long the buffer should be, two modes are supported:
//   1. If buffer == 0, only return the number of bytes, don't write anything.
//   2. If buffer != 0, write data into the buffer and return the number of bytes written.

int pack(char *buffer, const char *format, ...){
    int bites_count=0;
    va_list ap;
    va_start(ap, format);
    // char char_cur;
    char* pointer;
    int cur_int;
    double cur_double;
    while(*format){
        // bites_count += va_arg(ap, int);
        format++; // pass %
        if(*format=='d'){
            bites_count+=4;
            //write in buffer
            
            cur_int = va_arg(ap, int);
            // printf("%d\n", cur_int);
            if(buffer){
                pointer = (char*) &cur_int;
                for(int i=0; i<4;i++){
                    *buffer = pointer[i];
                    buffer++;
                }
            }
        }else if(*format=='l' && *(format+1)=='f'){
            format++;
            bites_count+=8;
            //write in buffer
            cur_double = va_arg(ap, double);
            // printf("%lf\n", cur_double);
            if(buffer){
                pointer = (char*) &cur_double;
                for(int i=0; i<8;i++){
                    *buffer = pointer[i];
                    buffer++;
                }
            }
        }else if(*format=='s'){
            char* cur = va_arg(ap, char*);
            // printf("%s\n", cur);

            while (1){
                bites_count+=1;
                if(buffer){
                    *buffer = *cur;
                    buffer++;
                }
                if(*cur=='\0'){
                    break;
                }
                cur++;
            }
            
        }
        
        //move to the next
        format++;
    }


    va_end(ap);
    return bites_count;
}