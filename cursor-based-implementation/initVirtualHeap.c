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
void insertLast(VirtualHeap* L, List* A, char elem);
void deleteFirst(VirtualHeap* L, List* head);
void deleteLast(VirtualHeap* L, List* head);
void traversal(VirtualHeap B, int A);
void checkAvailSpace(VirtualHeap A);

int main(){
    VirtualHeap B;
    initVirtualHeap(&B);
    List head;
    initList(&head);
    insertLast(&B, &head, 'u'); //0
    insertLast(&B, &head, 'c'); //1
    insertLast(&B, &head, 'k'); //2
    insertFirst(&B, &head, 'f'); //3
    traversal(B, head);
    checkAvailSpace(B);
    deleteLast(&B, &head);
    traversal(B, head);
    printf("\t(%d, %d)\n", head, B.avail);
    checkAvailSpace(B);
    return 0;
}

void deleteLast(VirtualHeap* L, List* head){
    if(*head != -1){
        List B;
        for(B = *head; L->nodes[L->nodes[B].link].link != -1; B = L->nodes[B].link){}
        List oldLastNode = L->nodes[B].link;
        List oldAvail = L->avail;
        L->nodes[B].link = -1;
        L->avail = oldLastNode;
        L->nodes[oldLastNode].link = oldAvail;
    }
}

void deleteFirst(VirtualHeap*  L, List* head){
    if(*head != -1){
        List oldAvail = L->avail, oldNode = *head;
        *head = L->nodes[oldNode].link;
        L->avail = oldNode;
        L->nodes[oldNode].link = oldAvail;        
    }
    
}

void traversal(VirtualHeap B, int A){ 
    for(;A != -1; A = B.nodes[A].link){
        printf("%c", B.nodes[A].data);
    }
    printf("\n");
}

void checkAvailSpace(VirtualHeap A){
    for(;A.avail != -1; A.avail = A.nodes[A.avail].link){
        printf("Node: %d is Available\n", A.avail);
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


void insertLast(VirtualHeap* L, List *A, char elem){
    if(L->avail != - 1){
        List B;
        for(B = *A; L->nodes[B].link != -1; B = L->nodes[B].link){}
        List temp = L->avail;
        L->nodes[B].link = temp;
        L->nodes[temp].data = elem;
        L->avail = L->nodes[temp].link;
        L->nodes[temp].link = -1;
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
