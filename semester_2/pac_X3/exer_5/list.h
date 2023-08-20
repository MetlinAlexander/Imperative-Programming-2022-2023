#include <stdlib.h>

#define REALLYCONCAT(P, S) P##S
#define CONCAT(Prefix, Suffix) REALLYCONCAT(Prefix, Suffix)

#define LIST CONCAT(List_, T)

typedef struct LIST {
    T val;
    struct LIST* next;
} LIST;

// по списку итерироваться
void CONCAT(visitList_, T)(LIST* list, void (*fn)(T)) {
    for ( ; list != NULL; list = list->next) {
        fn(list->val);
    }
}

// вставка элемена для удобного создания списков:
LIST *CONCAT(LIST, _push)(LIST* list, T newVal) {
    LIST *newElem = (LIST *)malloc(sizeof(LIST));
    newElem->val = newVal;
    newElem->next = list;
    return newElem;
}

#undef LIST