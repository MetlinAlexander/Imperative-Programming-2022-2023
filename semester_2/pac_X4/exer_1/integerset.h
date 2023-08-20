typedef struct IntegerSet_s{
    int* set;
    int size_set;
}IntegerSet;

IntegerSet* CreateSet(int* arr, int size);
int IsInSet(IntegerSet* cur_set, int elem);

