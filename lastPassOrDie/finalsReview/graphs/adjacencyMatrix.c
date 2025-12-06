#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char f[24], l[16], MI;
}name;

typedef struct{
    int id;
    name lol;
    char course[8];
    int yr;
}stud;

int main(){
    stud a = {1,{"XXXX","XXXX",'X'}, "XXXX", 2};
    printf("%s", a.lol.f);
}