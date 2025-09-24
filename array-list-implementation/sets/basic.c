#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int elems[MAX];
    int count;
}Set;

void insert(Set* A, int x);
void init(Set* A);
void delete(Set* A, int x);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);
Set mergeSortedSets(Set A, Set B);
Set mergeUnsortedSets(Set A, Set B);

int main(){

}

void insert(Set* A, int x){
    if(A->count < MAX){
        int ndx;
        for(ndx = 0; ndx < A->count && A->elems[ndx] != x; ndx++){} // to avoid duplicates this checks if x is already in the set
        if(ndx == A->count){
            A->elems[A->count++] = x;
        }
    }
}

void init(Set* A){
    A->count = 0;
}

void delete(Set* A, int x){
    
}

Set Union(Set A, Set B){
    //assume unsorted
    Set C = A;
    for(int ndx = 0; ndx < B.count; ndx++){
        insert(&C, B.elems[ndx]);
    }  
    
    return C;
}

Set Intersection(Set A, Set B){
    Set C = {{}, 0};
    for(int ndx = 0; ndx < A.count; ndx++){
        int idx;
        for(idx = 0; idx < B.count && A.elems[ndx] != B.elems[idx]; idx++){}
        if(idx < B.count){
            C.elems[C.count++] = A.elems[ndx];
        }
    }
    
    return C;
}

Set Difference(Set A, Set B){
    Set C = {{}, 0};
    for(int ndx = 0; ndx < A.count; ndx++){
        int idx;
        for(idx = 0; idx < B.count && A.elems[ndx] != B.elems[idx]; idx++){}
        if(idx == B.count){
            C.elems[C.count++] = A.elems[ndx];
        }
    }
    
    return C;
}

Set mergeSortedSets(Set A, Set B){

}

Set mergeUnsortedSets(Set A, Set B){
    
}

