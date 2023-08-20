#include "logger.h"
#include <stdio.h>
#include <stdarg.h>    

FILE * cur_file = 0;
int calls = 0;


// If file != 0, then enables logging and sets current logfile.
// All the messages printed by logPrintf go into this file afterwards.
// If file = 0, disables logging (logPrintf does nothing afterwards).
// Logging is also disabled initially.
// The file is NOT closed when logging is disabled.
void logSetFile(FILE *file){
    cur_file = file;
}

// Prints text message to the current logfile (with printf formatting).
// If logging is disabled, then it does nothing.
void logPrintf(const char *format, ...){
    //check if enable
    if(cur_file == 0) {
        return ;
    }
    //enable
    calls+=1;
    va_list ap;
    va_start(ap, format);
    vfprintf(cur_file, format, ap);
    va_end(ap);
}

// Returns the number of successful logPrintf calls since program start.
// A call is considered unsuccessful when logging is disabled.
int getLogCallsCount(){
    return calls;
}