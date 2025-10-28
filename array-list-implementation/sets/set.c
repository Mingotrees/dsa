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
void display(Set A);
Set UnionSorted(Set A, Set B);
Set IntersectionSorted(Set A, Set B);
Set DifferenceSorted(Set A, Set B);

int main(){
    Set A, B;
    init(&A); init(&B);
    for(int ndx = 0; ndx < 4; ndx++){
        insert(&A, ndx);
        insert(&B, ndx+2);
    }
    insert(&A, 7);
    display(A);
    display(B);
    printf("Union of A and B:\n");
    Set C = UnionSorted(A, B);
    display(C);

    printf("Intersection of A and B:\n");
    C = IntersectionSorted(A, B);
    display(C);

    printf("Difference of A and B:\n");
    C = DifferenceSorted(A, B);
    display(C);
}

void display(Set A){
    printf("SET ELEMENTS\n");
    for(int ndx = 0; ndx < A.count; ndx++){
        printf("[%d]: %d\n", ndx, A.elems[ndx]);
    }
    printf("\n");
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
    //order doesnt matter
    int ndx;
    for(ndx = 0; ndx < A->count && A->elems[ndx] != x; ndx++){}
    if(ndx < A->count){
        A->count--;
        A->elems[ndx] = A->elems[A->count]; 
    }
}

Set UnionSorted(Set A, Set B){
    //this actually work with both sorted and unsorted
    // Set C = A;
    // for(int ndx = 0; ndx < B.count; ndx++){
    //     insert(&C, B.elems[ndx]); // O(n^2) though
    // }
    
    //for sorted only O(n) kinda lengthy
    Set C;
    init(&C);
    int aCount = 0;
    int bCount = 0;
    while(bCount < B.count && aCount < A.count){
        if(A.elems[aCount] < B.elems[bCount]){
            C.elems[C.count] = A.elems[aCount];
            aCount++;
        }else{
            if(A.elems[aCount] == B.elems[bCount]){
                aCount++;
            }
            C.elems[C.count] = B.elems[bCount];
            bCount++;
        }
        C.count++;
    }

    if(aCount == A.count){
        while(bCount < B.count){
            C.elems[C.count++] = B.elems[bCount++];
        }
    }else{
        while(aCount < A.count){
            C.elems[C.count++] = A.elems[aCount++];
        }
    }

    //this is a one pass solution but it takes a lot of lines

    
    return C;
}

Set IntersectionSorted(Set A, Set B){
    Set C = {{}, 0};
    // for(int ndx = 0; ndx < A.count; ndx++){
    //     int idx;
    //     for(idx = 0; idx < B.count && A.elems[ndx] != B.elems[idx]; idx++){}
    //     if(idx < B.count){
    //         C.elems[C.count++] = A.elems[ndx];
    //     }
    // }
    int bCount = 0;
    int aCount = 0;
    while(aCount < B.count && bCount < A.count){
        if(A.elems[aCount] < B.elems[bCount]){
            aCount++;
        }else{
            if(A.elems[aCount] == B.elems[bCount]){
                C.elems[C.count] = B.elems[bCount];
                C.count++;
                aCount++;
            }
            bCount++;
        }
    }
    //one pass solution for sorted sets vv efficient O(n)

    
    return C;
}

Set DifferenceSorted(Set A, Set B){
    Set C = {{}, 0};
    // for(int ndx = 0; ndx < A.count; ndx++){
    //     int idx;
    //     for(idx = 0; idx < B.count && A.elems[ndx] != B.elems[idx]; idx++){}
    //     if(idx == B.count){
    //         C.elems[C.count++] = A.elems[ndx];
    //     }
    // }
    int aCount = 0;
    int bCount = 0;
    while(bCount < B.count && aCount < A.count){
        if(A.elems[aCount] < B.elems[bCount]){
            C.elems[C.count] = A.elems[aCount];
            aCount++;
            C.count++;
        }else{
            if(A.elems[aCount] == B.elems[bCount]){
                aCount++;
            }
            bCount++;
        }
    }

    while(aCount < A.count){
        C.elems[C.count++] = A.elems[aCount++];
    }
    
    return C;
}



