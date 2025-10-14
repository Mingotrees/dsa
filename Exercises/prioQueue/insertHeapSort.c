#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  SIZE 0xFF

typedef struct {
   int elem[SIZE];
   int count;
}maxHeap, minHeap;

void insertMinHeap(minHeap* a, int x);
void insertAllMinHeap(minHeap* a);
int deleteMin(minHeap* a);
void heapSort(minHeap* a);
void populate(minHeap* a);
void display(minHeap a);

int main(){
    minHeap A;
    populate(&A);
    display(A);
    heapSort(&A);
}

void insertMinHeap(minHeap* a, int x){
    int insertPos = a->count++;
    int parent = (insertPos-1)/2;
    while(insertPos > 0 && a->elem[parent] > x){
        a->elem[insertPos] = a->elem[parent];
        insertPos = parent;
        parent = (parent-1)/2;
    }
    a->elem[insertPos] = x;
}

void insertAllMinHeap(minHeap* a){
    int oldSize = a->count;
    a->count = 0;
    for(int ndx = 0; ndx < oldSize; ndx++){
        insertMinHeap(a, a->elem[ndx]);
    }
}

int deleteMin(minHeap* a){
    int root = a->elem[0];
    int newRoot = a->elem[--a->count];
    int parent = 0, flag = 0;
    int child = 1;
    while(child < a->count && flag != 1){
        if((child + 1) < a->count && a->elem[child + 1] < a->elem[child]){
            child++;
        }
        
        if(newRoot <= a->elem[child]){
            flag = 1;
        }else{
            a->elem[parent] = a->elem[child];
            parent = child;
            child = parent * 2 + 1;
        }
    }

    a->elem[parent] = newRoot;

    return root;
}

void heapSort(minHeap* a){
    insertAllMinHeap(a);
    printf("Heapified: ");
    display(*a);
    int oldSize = a->count;
    while(a->count > 1){
        int store = deleteMin(a);
        a->elem[a->count] = store;
    }
    a->count = oldSize;
    printf("Sorted: ");
    display(*a);
}

void populate(minHeap* a) {
    srand(time(NULL)); 
    a->count = 0;
    for (int i = 0; i < 5; i++) {
        a->elem[a->count++] = rand() % 100; 
    }
}

void display(minHeap a){
    for(int ndx = 0; ndx < a.count; ndx++){
        printf("%d ", a.elem[ndx]);
    }
    printf("\n");
}
