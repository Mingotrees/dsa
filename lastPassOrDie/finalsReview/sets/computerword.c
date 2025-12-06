#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 8

typedef unsigned char Set;

void insert(Set*, int);
void delete(Set*, int);
bool is_member(Set, int);
Set Union(Set, Set);
Set Intersection(Set, Set);
Set Difference(Set, Set);
void init_set(Set*);
void display(Set, char[]);


int main(){
    Set A, B;
    init_set(&A); init_set(&B);
    for(int ndx = 0; ndx < 4; ndx++){
        insert(&A, ndx);
        insert(&B, ndx+2);
    }
    insert(&A, 7);
    display(A, "SET A");
    display(B, "SET B");
    Set C = Union(A, B);
    display(C, "UNION OF A & B");

    C = Intersection(A, B);
    display(C, "INTERSECTION OF A & B");

    C = Difference(A, B);
    display(C, "DIFFERENCE OF A & B");

    printf("%s", is_member(C, 9) == true ? "Member" : "Not Member");
}

void insert(Set* A, int x){
    if(x < MAX){
        *A |= (1u << x);
    }else{
        printf("bruh");
    }
}
void delete(Set*A, int x){
    if(x < MAX){
        *A &= ~(1u << x);
    }
}

bool is_member(Set A, int x){
    if(x < MAX){
        return (1u << x & A) > 0 ? true : false;
    }else{
        return false;
    }
}

Set Union(Set A, Set B){
    return A|B;
}
Set Intersection(Set A, Set B){
    return A&B;
}

Set Difference(Set A, Set B){
    return A&~B;
}
void init_set(Set* A){
    *A = 0;
}

void display(Set A, char message[]){
    printf("%s: ", message);
    for(int ndx = 0; ndx < MAX; ndx++){
        if((1u << ndx & A) > 0){
            printf("%d ", ndx);
        }
    }
    printf("\n");

    Set mask;
    for(mask = 1 << sizeof(Set)*8-1; mask > 0; mask >>= 1){
        printf("%d ", mask & A > 0 ? 1 : 0);
    }
    printf("\n");
}