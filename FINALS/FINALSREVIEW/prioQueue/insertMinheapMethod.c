#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int arr[MAX];
    int count; 
}Tree;

void display(Tree);
void insert(Tree*, int);
int deleteMin(Tree*);
void heapsort(Tree*);
void insertAllMinheap(Tree*);


int main(){
    Tree T = {{20, 5, 15, 22, 9, 13, 27, 3, 8}, 9};
    display(T);
    
    printf("\nHeapifying...\n");
    insertAllMinheap(&T);
    display(T);

    printf("\nDeleting min element: %d\n", deleteMin(&T));
    display(T);
    
    printf("\nNow performing heapsort...\n");
    heapsort(&T);
    display(T);
}

void display(Tree T){
    for(int ndx = 0; ndx < T.count; ndx++){
        printf("%d ", T.arr[ndx]);
    }
    printf("\n");
}

//heapify up
void insert(Tree* T , int x){
    if(T->count < MAX){
        int hole = T->count++;
        int parent = (hole-1)/2;
        while(hole > 0 && T->arr[parent] > x){
            T->arr[hole] = T->arr[parent];
            hole = parent;
            parent = (parent-1)/2;
        }
        T->arr[hole] = x;
    }
}

//heapify down
int deleteMin(Tree* T){
    int temp = T->arr[0];
    int ins = T->arr[--T->count];
    int parentNdx = 0; //where we insert in this method
    int child = 1;
    while(child < T->count){
        if(child + 1 < T->count && T->arr[child + 1] <  T->arr[child]){
            child++;
        }

        if(T->arr[child] < ins){
            T->arr[parentNdx] = T->arr[child];
            parentNdx = child;
            child = child * 2 + 1;
        }else{
            break;
        }
    }
    T->arr[parentNdx] = ins;
    return temp;
}

void heapsort(Tree* T){
    // insertAllMinheap(T);
    int oldCount = T->count;
    int end = oldCount - 1;
    while(T->count){
        int temp = deleteMin(T);
        T->arr[end--] = temp;
    }
     T->count = oldCount;
}

//kind of heapify
void insertAllMinheap(Tree* T){
    int oldCount = T->count;
    T->count = 0;
    int ndx = 0;
    while(ndx < oldCount){
        insert(T, T->arr[ndx++]);
    }
}
