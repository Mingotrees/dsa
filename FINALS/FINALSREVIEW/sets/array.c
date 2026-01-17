#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}Set;

void insert(Set*, int);
void delete(Set*, int);
bool is_member(Set*, int);
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
}

void insert(Set* A, int x){
    if(A->count < MAX){
        A->data[A->count++] = x;
    }else{
        printf("Full\n");
    }
}
void delete(Set* A, int x){
    int ndx;
    for(int ndx = 0; ndx < A->count && A->data[ndx] != x; ndx++){}
    if(ndx < A->count){
        A->data[ndx] = A->data[--(A->count)];
    }else{
        printf("not found\n");
    }
}
bool is_member(Set* A, int x){
    int ndx;
    for(int ndx = 0; ndx < A->count && A->data[ndx] != x; ndx++){}

    return ndx < A->count ? true : false;
}

Set Union(Set A, Set B){
    Set C;
    init_set(&C);
    memcpy(C.data, A.data, sizeof(int)*A.count);
    C.count = A.count;
    int ndx;
    for(ndx = 0; ndx < B.count; ndx++){
        int idx;
        for(idx = 0; idx < A.count && A.data[idx] != B.data[ndx]; idx++){}
        if(idx >= A.count) insert(&C, B.data[ndx]); 
    }

    return C;
}

Set Intersection(Set A, Set B){
    Set C;
    init_set(&C);
    int ndx;
    for(ndx = 0; ndx < B.count; ndx++){
        int idx;
        for(idx = 0; idx < A.count && A.data[idx] != B.data[ndx]; idx++){}
        if(idx < A.count) insert(&C, B.data[ndx]);
    }

    return C;
}

//A-B
Set Difference(Set A, Set B){
    Set C;    
    init_set(&C);
    int ndx;
    for(ndx = 0; ndx < A.count; ndx++){
        int idx;
        for(idx = 0; idx < B.count && B.data[idx] != A.data[ndx]; idx++){}
        if(idx == B.count) insert(&C, A.data[ndx]);
    }

    return C;
}

void init_set(Set* A){
    A->count = 0;
}

void display(Set A, char message[]){
    printf("%s: ", message);
    for(int ndx = 0; ndx < A.count; ndx++){
        printf("%d ", A.data[ndx]);
    }
    printf("\n");
}