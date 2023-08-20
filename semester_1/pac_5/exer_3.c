#include <stdio.h>

typedef struct Label_s{
    char name[16]; //имя автора (заканчивается нулём)
    int age;       //возраст автора (сколько лет)
} Label;

typedef struct NameStats_s{
    int cntTotal; //сколько всего подписей
    int cntLong;  //сколько подписей с именами длиннее 10 букв
} NameStats;

typedef struct AgeStats_s{
    int cntTotal;  //сколько всего подписей
    int cntAdults; //сколько подписей взрослых (хотя бы 18 лет)
    int cntKids;   //сколько подписей детей (меньше 14 лет)
} AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges){
    for(int i=0; i< cnt; i++){
        oNames->cntTotal++;
        oAges->cntTotal++;
        int ln=0;
        for(int j=0; arr[i].name[j]; j++){
            ln++;
        }
        if(ln>10) oNames->cntLong++;
        if(arr[i].age>=18) oAges->cntAdults++;
        if(arr[i].age<14) oAges->cntKids++;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Label a[n];
    // scan strings
    for (int i = 0; i < n; i++){
        scanf("%s %d let", &a[i].name, &a[i].age);
    }
    // analize strings
    NameStats name;
    name.cntLong=0, name.cntTotal=0;
    AgeStats age;
    age.cntAdults=0, age.cntKids=0, age.cntTotal=0;

    calcStats(a, n, &name, &age);
    // print rezalts
    printf("names: total = %d\n", name.cntTotal);
    printf("names: long = %d\n", name.cntLong);
    printf("ages: total = %d\n", age.cntTotal);
    printf("ages: adult = %d\n", age.cntAdults);
    printf("ages: kid = %d\n", age.cntKids);

    /*
    names: total = 7
names: long = 2
ages: total = 7
ages: adult = 3
ages: kid = 2

    */
    return 0;
}