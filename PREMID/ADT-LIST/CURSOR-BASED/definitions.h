#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#define MAX 5

typedef struct{
    char data;
    int link;
}nodetype;

typedef struct{
    nodetype nodes[MAX];
    int avail;
}VirtualHeap;

typedef int List;

/*
* INITIALIZE FUNCTIONS
*
*/
void initVirtualHeap(VirtualHeap* L);
void initVirtualHeap2(VirtualHeap* L);
void initList(List* A);

/**
* INSERT OPERATIONS
*
*/
void insertFirst(VirtualHeap* L, List* A, char elem);
void insertLast(VirtualHeap* L, List* A, char elem);
void insertSorted(VirtualHeap* L, List* head, char elem);


/**
* DELETE OPERATIONS
*
*/
void deleteFirst(VirtualHeap* L, List* head);
void deleteLast(VirtualHeap* L, List* head);
void deleteElem(VirtualHeap* L, List* head, char elem);


void sort(VirtualHeap* L, List head);

/*
* HELPER FUNCTIONS
*
*/
void checkAvailSpace(VirtualHeap A);
void isFull();
void insertSuccess();
void deleteSuccess();
void traversal(VirtualHeap B, int A);
List allocSpace(VirtualHeap* L);
void deallocSpace(VirtualHeap* L, List index);

#endif