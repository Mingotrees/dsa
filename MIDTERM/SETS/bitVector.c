#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0xA

//many wasted bits using int
typedef int SET[MAX];

void display(SET A, char* str);
void insert(SET* A, int x);
void delete(SET* A, int x);
bool isSubset(SET A, SET B);
SET* init2();
SET* UNION(SET A, SET B);
SET* INTERSECTION(SET A, SET B);
SET* DIFFERENCE(SET A, SET B);
bool isMember(SET A, int x);

int main(){
    SET A = {0}, B = {0};
    insert(&A, 5);
    insert(&A, 3);
    insert(&A, 9);
    insert(&A, 1);
    insert(&A, 7);

    insert(&B, 2);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 9);
    insert(&B, 10);

    display(A, "SET A");
    display(B, "SET B");
    SET* C = UNION(A, B);
    display(*C, "UNION OF SET A & B");
    free(C);
    C = INTERSECTION(A, B);
    display(*C, "INTERSECTION OF SET A & B");
    free(C);
    C = DIFFERENCE(A, B);
    display(*C, "DIFFERENCE OF SET A & B");
    free(C);
}

void display(SET A, char* str){
    printf("%s:{", str);
    for(int ndx = 0; ndx < MAX; ndx++){
        printf("%d", A[ndx]);
        if(ndx != MAX-1){
            printf(", ");
        }
    }
    printf("}\n");
}

void insert(SET* A, int x){
    if(x < MAX){
        (*A)[x] |= 1;
    }
}

void delete(SET* A, int x){
    if(x < MAX){
        (*A)[x] &= 0;
    }
}

bool isSubset(SET A, SET B);


SET* init2(){
    return malloc(sizeof(SET));
}

SET* UNION(SET A, SET B){
    SET* C = init2();
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] | B[ndx];
    }

    return C;
}

SET* INTERSECTION(SET A, SET B){
    SET* C = init2();
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & B[ndx];
    }

    return C;
}

SET* DIFFERENCE(SET A, SET B){
    SET* C = init2();
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & ~B[ndx];
    }

    return C;
}

bool isMember(SET A, int x);