#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0xA

typedef struct{
    int arr[MAX];
    int count;
}SET;

void display(SET A, char* str);
void insert(SET* A, int x);
void initialize(SET* A);
void delete(SET* A, int x);
bool isSubset(SET A, SET B);
SET init2();
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
bool isMember(SET A, int x);


int main(){
    SET A = init2(), B = init2();
    insert(&A, 5);
    insert(&A, 3);
    insert(&A, 9);
    insert(&A, 1);
    insert(&A, 7);

    // insert(&B, 2);
    insert(&B, 3);
    // insert(&B, 6);
    insert(&B, 9);
    // insert(&B, 10);

    display(A, "SET A");
    display(B, "SET B");
    SET C = UNION(A, B);
    display(C, "UNION OF SET A & B");
    C = INTERSECTION(A, B);
    display(C, "INTERSECTION OF SET A & B");
    C = DIFFERENCE(A, B);
    display(C, "DIFFERENCE OF SET A & B");

    printf("B is %s", isSubset(A, B) ? "a subset of A" : "is not a subset of A");


}


void display(SET A, char* str){
    printf("%s: {", str);
    for(int ndx = 0; ndx < A.count; ndx++){
        printf("%d", A.arr[ndx]);
        if(ndx != A.count - 1){
            printf(", ");
        }
    }
    printf("}\n");
}


void insert(SET* A, int x){
    //RULES: order doesn't matter, no elements must exist more than once
    if(A->count != MAX){
        int ndx;
        for(ndx = 0; ndx < A->count && A->arr[ndx] != x; ndx++){}
        if(ndx == A->count){
            A->arr[A->count++] = x;
        }
    }
}

void initialize(SET* A){
    A->count = 0;
}

void delete(SET* A, int x){
    //since order doesn't matter we can just swap the last element with the one we delete cuh
    if(A->count > 0){
        int ndx;
        for(int ndx = 0; ndx < A->count && A->arr[ndx] != x; ndx++){}
        if(ndx < A->count){
            A->arr[ndx] = A->arr[--A->count];
        }
    }
}

bool isSubset(SET A, SET B){
    //the question is, is B a subset of A?
    //O(n * m) worst case
    bool flag = true;
    for(int ndx = 0; ndx < B.count && flag != false; ndx++){
        int idx;
        for(idx = 0; idx < A.count && A.arr[idx] != B.arr[ndx]; idx++){}
        if(idx == A.count){
            flag = false;
        }
    }
    return flag;
}

SET init2(){
    SET A = {.count = 0};
    return A;
}


//to do handle empty sets
SET UNION(SET A, SET B){
    SET C = A;
    int ndx; 
    //O(nm)
    for(ndx = 0; ndx < B.count; ndx++){
        int idx;
        for(idx = 0; idx < C.count && C.arr[idx] != B.arr[ndx]; idx++){}
        if(idx == C.count){
            C.arr[C.count++] = B.arr[ndx];
        }
    }
    //first implementation merge and delete //ineffcient O(n^2)
    // for(ndx = 0; ndx < B.count; ndx++){
    //     insert(&C, B.arr[ndx]);
    // }
    // int idx;
    // for(ndx = 0, idx = 0; ndx < C.count; ndx++){
    //     for(idx = A.count; idx < C.count; idx++){
    //         if(C.arr[idx] == C.arr[ndx]){
    //             C.arr[idx] = C.arr[--C.count];
    //         }else{
    //             idx++;
    //         }
    //     }
    // }
    return C;
}

SET INTERSECTION(SET A, SET B){
    SET C = {.count = 0};
    int ndx; 
    for(ndx = 0; ndx < A.count; ndx++){
        int idx;
        for(idx = 0; idx < B.count && B.arr[idx] != A.arr[ndx]; idx++){}
        if(idx < B.count){
            C.arr[C.count++] = A.arr[ndx];
        }
    }
    
    return C;
}

SET DIFFERENCE(SET A, SET B){
    //A not in B
    SET C = A;
    int ndx; 
    for(ndx = 0; ndx < B.count; ndx++){
        int idx;
        for(idx = 0; idx < C.count && C.arr[idx] != B.arr[ndx]; idx++){}
        if(idx < C.count){
            C.arr[idx] = C.arr[--C.count];
        }
    }
    
    return C;
}

bool isMember(SET A, int x){
    int ndx;
    for(ndx = 0; ndx < A.count && A.arr[ndx] != x; ndx++){}
    return ndx < A.count ? true : false; 
}