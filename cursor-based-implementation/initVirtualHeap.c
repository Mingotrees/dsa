#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    char data;
    int link;
}nodetype;

typedef struct{
    nodetype nodes[MAX];
    int avail;
}VirtualHeap;

typedef int List;

void initVirtualHeap(VirtualHeap* L);
void initVirtualHeap2(VirtualHeap* L);
void initList(List* A);
void insertFirst(VirtualHeap* L, List* A, char elem);
void traversal(VirtualHeap B, int A);

int main(){
    VirtualHeap B;
    initVirtualHeap(&B);
    List head;
    initList(&head);
    insertFirst(&B, &head, 'c');
    insertFirst(&B, &head, 's');
    insertFirst(&B, &head, 'u');
    traversal(B, head);

    return 0;
}

void traversal(VirtualHeap B, int A){ 
    for(;A != -1; A = B.nodes[A].link){
        printf("%c", B.nodes[A].data);
    }
}

void insertFirst(VirtualHeap* L, List* A, char elem){
    //0. Check avail if not -1;
    //1. Populate Node
    //2. Update Avail to Link Value
    //3. Update Link Value to -1 
    if(L->avail != -1){
        int spot = L->avail;
        L->nodes[spot].data = elem;
        L->avail = L->nodes[spot].link;
        L->nodes[spot].link = *A;
        *A = spot;
    }
}

void initList(List* A){
    *A = -1;
}

//version 1
void initVirtualHeap(VirtualHeap* L){
    int A, mald = MAX - 1;
    L->avail = 0 ;
    for(A = 0; A < mald; A++){
        L->nodes[A].link = A + 1;
    }
    L->nodes[A].link = -1;
}

//version 2
void initVirutalHeap2(VirtualHeap* L){
    L->avail = MAX - 1;
    int A;
    for(A = L->avail; A >= 0; A--){
        L->nodes[A].link = A - 1;
    }
}
