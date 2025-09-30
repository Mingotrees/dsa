#include <stdio.h>
#define MAX 100

typedef struct{
    int data;
    int next;
}nodetype;

typedef struct{
    nodetype elems[MAX];
    int avail;
}VHeap;

typedef struct{
    VHeap* heap;
    int head;
}SET;

void insert(SET *A, int x);
void delete(SET *A, int x);
void display(SET A);
void initializeSet(SET* A);
void initializeHeap(VHeap* A);
int allocSpace(VHeap *A);
void deallocSpace(VHeap *A, int x);
SET UnionSorted(SET A, SET B);
SET IntersectionSorted(SET A, SET B);
SET DifferenceSorted(SET A, SET B);

int main(){
    VHeap rad;
    initializeHeap(&rad);
    SET A = {&rad}, B = {&rad};
    initializeSet(&A);
    initializeSet(&B);

    for(int ndx = 0; ndx < 10; ndx++){
        insert(&A, 10 - ndx);
        insert(&B, 15 - ndx);
    }

    printf("SET: A\n");
    display(A);

    printf("SET: B\n");
    display(B);


    SET C = UnionSorted(A, B);
    printf("Union: \n");
    display(C);

    C = IntersectionSorted(A, B);
    printf("Intersection: \n");
    display(C);

    C = DifferenceSorted(A, B);
    printf("Difference: \n");
    display(C);


}

int allocSpace(VHeap *A)
{
    int temp = A->avail;
    if(temp != -1){
        A->avail = A->elems[temp].next;
    }

    return temp;
}

void initializeHeap(VHeap* A)
{
    A->avail = MAX - 1;
    for(int i = 0; i < MAX; i++){
        A->elems[i].next = i - 1;
    }
}

void initializeSet(SET* A)
{
    A->head = -1;
}

void insert(SET* A, int x)
{
    int space = allocSpace(A->heap);
    if(space != -1){
        A->heap->elems[space].data = x;
        A->heap->elems[space].next = A->head;
        A->head = space;
    }
}

void delete(SET *A, int x)
{    
    int *ndx; 
    for(ndx = &A->head; *ndx != -1 && A->heap->elems[*ndx].data != x; ndx = &A->heap->elems[*ndx].next){} //PPN
    if(*ndx != -1){
        int temp = *ndx;
        *ndx = A->heap->elems[*ndx].next;
        deallocSpace(A->heap, temp);
    }
}

/*
0 [][-1]
1 [][0] A->avail = 2;
2 [1][1]
*/

void deallocSpace(VHeap *A, int x){
    if(x != -1){
        A->elems[x].next = A->avail;
        A->avail = x;
    }
}

void display(SET A)
{
    printf("SET ELEMENTS: {");
    for(int ndx = A.head; ndx != -1; ndx = A.heap->elems[ndx].next){
        printf(" %d", A.heap->elems[ndx].data);
    }
    printf(" }\n");
}


SET UnionSorted(SET A, SET B)
{
    SET C = {A.heap, -1};
    int* ndx;
    for(ndx = &C.head; A.head != -1 && B.head != -1; ndx = &(C.heap->elems[*ndx].next)){
        int space = allocSpace(C.heap);
        if(space != -1){
            if(A.heap->elems[A.head].data <  A.heap->elems[B.head].data){ //this works because they live in the same heap honestly
                C.heap->elems[space].data = A.heap->elems[A.head].data;
                A.head = A.heap->elems[A.head].next;
            }else{                                                             
                if(A.heap->elems[A.head].data == A.heap->elems[B.head].data){
                    A.head = A.heap->elems[A.head].next;
                }
                C.heap->elems[space].data = B.heap->elems[B.head].data;
                B.head = B.heap->elems[B.head].next;
            }
            *ndx = space;
        }

    }

    if(A.head == -1){
        A.head = B.head;
    }

    while(A.head != -1){
        int space = allocSpace(C.heap);
        if(space != -1){
            C.heap->elems[space].data = A.heap->elems[A.head].data;
            A.head = A.heap->elems[A.head].next;
            *ndx = space;
            ndx = &(C.heap->elems[*ndx].next);
        }
    }

    *ndx = -1;
    return C;
}

SET IntersectionSorted(SET A, SET B)
{
    SET C = {A.heap, -1};
    int* cPtr;
    for(cPtr = &C.head; A.head != -1 && B.head != -1; ){
        if(A.heap->elems[A.head].data < B.heap->elems[B.head].data){
            A.head = A.heap->elems[A.head].next;
        }else{
            if(A.heap->elems[A.head].data == B.heap->elems[B.head].data){
                int space = allocSpace(C.heap);
                if(space != -1){
                    C.heap->elems[space].data = A.heap->elems[A.head].data;
                    *cPtr = space;
                    cPtr = &(C.heap->elems[*cPtr].next);
                    A.head = A.heap->elems[A.head].next;  
                }
            }
            B.head = B.heap->elems[B.head].next;
        }   
    }

    *cPtr = -1;
    return C;
}

// 1 2 3
// 2 3 4 
// 1 

SET DifferenceSorted(SET A, SET B)
{
    SET C = {A.heap, -1};
    int* cPtr;
    for(cPtr = &C.head; A.head != -1 && B.head != -1; ){
        if(A.heap->elems[A.head].data < B.heap->elems[B.head].data){
            int space = allocSpace(C.heap);
            C.heap->elems[space].data = A.heap->elems[A.head].data;
            *cPtr = space;
            cPtr = &(C.heap->elems[*cPtr].next);
            A.head = A.heap->elems[A.head].next;
        }else{
            if(A.heap->elems[A.head].data == B.heap->elems[B.head].data){
                A.head = A.heap->elems[A.head].next;            
            }else{
                int space = allocSpace(C.heap);
                C.heap->elems[space].data = A.heap->elems[A.head].data;
                *cPtr = space;
                cPtr = &(C.heap->elems[*cPtr].next);
            }
            B.head = B.heap->elems[B.head].next;
        }   
    }

    *cPtr = -1;
    return C;
}