#include <stdio.h>
#define MAX 8

typedef unsigned int SET;

void initialize(SET*);
void display(int);
void insert(int a, SET* A);
void delete(SET* A, int x);

int main(){
    SET a;
    initialize(&a);
    // display(a);
    // insert(1, &a);
    insert(7, &a);
    insert(6, &a);
    display(a);
    // delete(&a, 2);
    // display(a);
}

void display(int a)
{
    unsigned int x = 1 << sizeof(int)* MAX -1;
    for(;x!=0; x >>= 1){
        printf("%d ", (x&a) == 0 ? 0 : 1);
    }
    printf("\nUniversal Set: %d", a);
    printf("\n");
}

void initialize(SET* a){
    *a = 0;
}

void insert(int a, SET* A){
    unsigned int mask = 1 << sizeof(int)*a;
    *A  = *A | mask;
}

void delete(SET* A, int x){
    if((*A & x) != 0){
        *A = *A ^ x;
    }else{
        printf("Element is not in the set");
    }
}