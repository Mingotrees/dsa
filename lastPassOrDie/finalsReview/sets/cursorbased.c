#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 20

typedef struct{
    int data;
    int next;
}nodetype;

typedef struct {
    nodetype arr[MAX];
    int avail;
}Vheap;

typedef struct{
    Vheap* mem;
    int root;
}Set;


int alloc(Vheap*);
void dealloc(Vheap*, int x);
void insert(Set*, int);
void delete(Set*, int);
bool is_member(Set, int);
Set Union(Set, Set);
Set Intersection(Set, Set);
Set Difference(Set, Set);
void init_set(Set*);
void display(Set, char[]);


int main(){
    Set A;
    init_set(&A);
    Set B = {A.mem, -1};
    for(int ndx = 0; ndx < 4; ndx++){
        insert(&A, ndx);
        insert(&B, ndx+2);
    }
    insert(&A, 7);
    display(A, "SET A");
    display(B, "SET B");
    Set C = Union(A, B);
    display(C, "UNION OF A & B");

    // C = Intersection(A, B);
    // display(C, "INTERSECTION OF A & B");

    // C = Difference(A, B);
    // display(C, "DIFFERENCE OF A & B");

    // printf("%s", is_member(C, 9) == true ? "Member" : "Not Member");
}

int alloc(Vheap* A){
    int temp = A->avail;
    if(temp != -1){
        A->avail = A->arr[temp].next;
    }
    return temp;
}

void dealloc(Vheap* A, int x){
    A->arr[x].next = A->avail;
    A->avail = x;
}

void insert(Set* A, int x){
    int* ndx;
    for(ndx = &A->root; *ndx != -1 && A->mem->arr[*ndx].data != x; ndx = &(A->mem->arr[*ndx].next)){}
    if(*ndx == -1){
        int space = alloc(A->mem);
        A->mem->arr[space].data = x;
        A->mem->arr[space].next = -1;
        *ndx = space;
    }
}
void delete(Set* A, int x){
    int* ndx;
    for(ndx = &A->root; *ndx != -1 && A->mem->arr[*ndx].data != x; ndx = &(A->mem->arr[*ndx].next)){}
    if(*ndx != -1){
        int temp = *ndx;
        *ndx = A->mem->arr[temp].next;
        dealloc(A->mem, temp);
    }
}

bool is_member(Set A, int x){
    int ndx;
    for(ndx = A.root; ndx != -1 && A.mem->arr[ndx].data != x; ndx = A.mem->arr[ndx].next){}
    return ndx != -1 ? true : false;
}

Set Union(Set A, Set B){
    Set C = {A.mem, -1};
    int ndx;
    for(ndx = A.root; ndx != -1; ndx = A.mem->arr[ndx].next){insert(&C, A.mem->arr[ndx].data);}
    for(ndx = B.root; ndx != -1; ndx = B.mem->arr[ndx].next){insert(&C, B.mem->arr[ndx].data);}

    return C;
}

Set Intersection(Set A, Set B){

}

Set Difference(Set A, Set B){

}

//only applicable for the very first set
void init_set(Set* A){
    A->mem = (Vheap*)malloc(sizeof(Vheap));
    A->mem->avail = MAX-1;
    for(int ndx = 0; ndx < MAX; ndx++){
        A->mem->arr[ndx].next = ndx - 1;
    }
    A->root = -1;
}

void display(Set A, char message[]){
    printf("%s: ", message);
    while(A.root != -1){
        printf("%d ", A.mem->arr[A.root].data);
        A.root = A.mem->arr[A.root].next;
    }
    printf("\n");
}
