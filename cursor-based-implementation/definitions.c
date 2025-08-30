#include <stdio.h>
#include "definitions.h"

void isFull(){
    printf("No More Space Available\n");
}

void insertSuccess(){
    printf("Node Inserted Successfully\n");
}

void deleteSuccess(){
    printf("Node Deleted Sucessfully\n");
}

void insertSorted(VirtualHeap* L, List* head, char elem){
    int spot = allocSpace(L);
    if(spot != -1){
        List* pat;
        for(pat = head; *pat != -1 && L->nodes[*pat].data < elem; pat = &L->nodes[*pat].link){}
        List temp = *pat;
        L->nodes[spot].data = elem;
        L->nodes[spot].link = temp;
        *pat = spot; 
        insertSuccess();
    }else{
        isFull();
    }
}

void deleteElem(VirtualHeap* L, List* head, char elem){
    List* pat;
    for(pat = head; *pat != -1 && L->nodes[*pat].data != elem; pat = &L->nodes[*pat].link){}
    if(*pat != -1){
        List nextNode = L->nodes[*pat].link;
        deallocSpace(L, *pat);
        *pat = nextNode;
    }else{
        deleteSuccess();
    }
}

void deallocSpace(VirtualHeap* L, List index){
    if(index != -1){
        List temp = L->avail;
        L->nodes[index].link = temp;
        L->avail = index;
    }
}

List allocSpace(VirtualHeap* L){
    List temp = L->avail;
    if(temp != -1 ){
        L->avail = L->nodes[temp].link;
    }

    return temp;
}


void deleteLast(VirtualHeap* L, List* head){
    if(*head != -1){
        List *B;
        for(B = head; L->nodes[*B].link != -1; B = &L->nodes[*B].link){}
        List oldLastNode = *B;
        *B = -1;
        deallocSpace(L, oldLastNode);
        deleteSuccess();
    }
}

void deleteFirst(VirtualHeap*  L, List* head){
    if(*head != -1){
        List oldNode = *head;
        *head = L->nodes[oldNode].link;
        deallocSpace(L, oldNode);  
        deleteSuccess();
    }
    
}

void traversal(VirtualHeap B, int A){ 
    for(;A != -1; A = B.nodes[A].link){
        printf("(%c, %d)\n", B.nodes[A].data, B.nodes[A].link);
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
    int spot = allocSpace(L);
    if(spot != -1){
        L->nodes[spot].data = elem;
        L->nodes[spot].link = *A;
        *A = spot;
        insertSuccess();
    }else{
        isFull();
    }
}


void insertLast(VirtualHeap* L, List *A, char elem){
    List spot = allocSpace(L);
    if(spot != - 1){
        List* B;
        for(B = A; *B != -1; B = &L->nodes[*B].link){}
        L->nodes[spot].data = elem;
        L->nodes[spot].link = -1;
        *B = spot;
        insertSuccess();
    }else{
        isFull();
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

void sort(VirtualHeap* L, List* head){
    if(*head != -1){
        List* B;
        for(B = head; *B != -1; B = &L->nodes[*B].link){
            List smallNdx = *B;
            List A;
            for(A = L->nodes[*B].link; A != -1; A = L->nodes[A].link){
                // printf("%d", L->nodes[A].link);
                if(L->nodes[A].data < L->nodes[smallNdx].data){
                    smallNdx = A; 
                }
            }
            if(smallNdx != *B){
                char temp = L->nodes[*B].data;
                L->nodes[*B].data = L->nodes[A].data;
                L->nodes[A].data = temp;
            }    
        }
    }
}