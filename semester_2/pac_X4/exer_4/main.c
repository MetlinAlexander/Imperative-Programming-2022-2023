#include <stdio.h>
#include <assert.h>
typedef struct State{
        char *regs[256];
} State;

#include "decls.h" //contains function declarations (chunk of code above)
State state;

// gcc core.c -shared -fPIC -o core.so
// gcc main.c core.so -o main -Wl,-rpath=.

int main()
{
    echo_2(&state, "hello", "world");
    echo_0(&state);
    echo_1(&state, "the_only_argument");
    echo_3(&state, "a", "b", "c");
    store_2(&state, "13", "thirteen");
    store_2(&state, "10", "ten");
    store_2(&state, "15", "fifteen");
    store_2(&state, "20", "twelve");
    echo_1(&state, "== state ==");
    printregs_0(&state);
    echo_1(&state, "== copying ==");
    print_1(&state, "13");
    print_1(&state, "15");
    copy_2(&state, "13", "15");
    print_1(&state, "13");
    print_1(&state, "15");
    echo_1(&state, "== clear ==");
    clear_1(&state, "10");
    clear_1(&state, "15");
    store_2(&state, "13", "thirteen_V2");
    printregs_0(&state);
    // printf("ok\n");
}
