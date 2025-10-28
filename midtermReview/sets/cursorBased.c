#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 0x1E

typedef struct{
    int data;
    int link;
}celltype;

typedef struct{
    celltype arr[MAX];
    int avail;
}VHeap;

typedef struct{
    int head;
    VHeap* heap;
}SET;

void display(SET A, char* str);
void insert(SET* A, int x);
void initialize(SET* A);
void delete(SET* A, int x);
bool isSubset(SET A, SET B);
int alloc(SET A);
void dealloc(SET A, int x);
// SET init2();
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
bool isMember(SET A, int x);

void freeList(SET* A) {
    int temp;
    while (A->head != -1) {
        temp = A->head;          // store current node
        A->head = A->heap->arr[temp].link; // move head to next
        dealloc(*A, temp);            // free old head
    }
}

int main(){
     SET A;
     initialize(&A); 
     SET B = {-1, A.heap};
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
    
    SET C = UNION(A, B);
    display(C, "UNION OF SET A & B");
    freeList(&C);
    C = INTERSECTION(A, B);
    display(C, "INTERSECTION OF SET A & B");
    freeList(&C);
    C = DIFFERENCE(A, B);
    display(C, "DIFFERENCE OF SET A & B");

    // printf("B is %s", isSubset(A, B) ? "a subset of A" : "is not a subset of A");
    // freeList(&C);
}

void display(SET A, char* str){
    printf("%s:{", str);
    while(A.head != -1){
        printf("%d", A.heap->arr[A.head].data);
        if(A.heap->arr[A.head].link != -1){
            printf(", ");
        }
        A.head = A.heap->arr[A.head].link;
    }
    printf("}\n");
}

int alloc(SET A){
    int space = A.heap->avail;
    if(space != -1){
       A.heap->avail = A.heap->arr[A.heap->avail].link; 
    }

    return space;
}

void dealloc(SET A, int x){
    A.heap->arr[x].link = A.heap->avail; 
    A.heap->avail = x;
}


//debating on getting space first before checking if there is duplicate or not
void insert(SET* A, int x){
    int* ndx;
    for(ndx = &A->head; *ndx != -1 && A->heap->arr[*ndx].data != x; ndx = &(A->heap->arr[*ndx].link)){}
    if(*ndx == -1){
        int space = alloc(*A);
        if(space != -1){
            A->heap->arr[space].data = x;
            A->heap->arr[space].link = -1;
            *ndx = space;
        }
    }
}

void initialize(SET* A){
    A->head = -1;
    A->heap = (VHeap*)malloc(sizeof(VHeap));
    A->heap->avail = MAX-1;
    for(int ndx = 0; ndx < MAX; ndx++){
        A->heap->arr[ndx].link = ndx - 1;
    }
}


void delete(SET* A, int x){
    int *ndx;
    for(ndx = &A->head; *ndx != -1 && A->heap->arr[*ndx].data != x; ndx = &(A->heap->arr[*ndx].link)){}
    if(*ndx != -1){
        int temp = *ndx;
        *ndx = A->heap->arr[temp].link;
        dealloc(*A, temp);
    }   
}

bool isSubset(SET A, SET B);
// SET init2();
SET UNION(SET A, SET B){
    int space, trav = A.head;
    SET C = {-1, A.heap};
    int *cPtr = &C.head;
    //can just use insert function it automatically checks uniqueness;
    while(trav != -1){
        space = alloc(C);
        if(space != -1){
            *cPtr = space;
            C.heap->arr[space].data = C.heap->arr[trav].data;
            cPtr = &(C.heap->arr[space].link); 
        }
        trav = A.heap->arr[trav].link;
    }

     //can just use insert function it automatically checks uniqueness;
    for(int ndx = B.head; ndx != -1; ndx = C.heap->arr[ndx].link){
        for(trav = C.head; trav != -1 && C.heap->arr[trav].data != C.heap->arr[ndx].data; trav = C.heap->arr[trav].link){}
        if(trav == -1){
            space = alloc(C);
            if(space != -1){
                *cPtr = space;
                C.heap->arr[space].data = C.heap->arr[ndx].data;
                cPtr = &(C.heap->arr[space].link); 
            }   
        }
    }

    *cPtr = -1;

    return C;
}

SET INTERSECTION(SET A, SET B){
    SET C = {-1, A.heap};
    int space;
    int *cPtr = &C.head;
    for(int ndx = A.head; ndx != -1; ndx = C.heap->arr[ndx].link){
        int trav;
        for(trav = B.head; trav != -1 && C.heap->arr[ndx].data != C.heap->arr[trav].data; trav = C.heap->arr[trav].link){}
        if(trav != -1){
            space = alloc(C);
            if(space != -1){
                *cPtr = space;
                C.heap->arr[space].data = C.heap->arr[ndx].data;
                cPtr = &(C.heap->arr[space].link); 
            }
        }
    }

    *cPtr = -1;
    return C;
}

SET DIFFERENCE(SET A, SET B){
    SET C = {-1, A.heap};
    int space;
    int *cPtr = &C.head;
    for(int ndx = A.head; ndx != -1; ndx = C.heap->arr[ndx].link){
        int trav;
        for(trav = B.head; trav != -1 && C.heap->arr[ndx].data != C.heap->arr[trav].data; trav = C.heap->arr[trav].link){}
        if(trav == -1){
            space = alloc(C);
            if(space != -1){
                *cPtr = space;
                C.heap->arr[space].data = C.heap->arr[ndx].data;
                cPtr = &(C.heap->arr[space].link); 
            }
        }
    }

    *cPtr = -1;
    return C;
}

bool isMember(SET A, int x);

