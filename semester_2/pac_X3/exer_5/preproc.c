#include <stdio.h>

#define T int
#include "list.h"
#undef T

typedef char const* str;
#define T str
#include "list.h"
#undef T

// Просто функции, печатающие значения указанных типов данных:
void print_int(int v) { printf("%d\n", v); }
void print_str(str s) { printf("%s\n", s); }

int main() {
    List_int* list_i = NULL;
    for (int i = 0; i < 5; ++i) {
        list_i = List_int_push(list_i, i);
    }
        
    List_str* list_s = NULL;
    list_s = List_str_push(list_s, "Hello");
    list_s = List_str_push(list_s, "world");
        
    visitList_int(list_i, print_int);
    visitList_str(list_s, print_str);
    return 0;
}