#include <stdio.h>
#define SIZE 0xFF

typedef struct{
    int elem[SIZE];
    int count;
}maxHeap, minHeap;

void insertMinHeap(minHeap*, int);
void insertAllMinHeap(minHeap*);
int deleteMin(minHeap*, int);
void heapSort(minHeap*);
void display(minHeap);

int main(){
    minHeap b = {{3,1,2,4,2,6,10,9}, 8};
    heapSort(&b);
}

void insertMinHeap(minHeap* a, int x){
    int hole = a->count++;
    int parent = (a->count-1)/2;
    while(hole > 0 && x < a->elem[parent]){
        a->elem[hole] = a->elem[parent];
        hole = parent;
        parent = (parent-1)/2;
    }
    a->elem[hole] = x;
}

void insertAllMinHeap(minHeap* a){
    int oldCount = a->count;
    a->count = 0;
    int ndx;
    for(ndx = 0; ndx < oldCount; ndx++){
        insertMinHeap(a, a->elem[ndx]);
    }
}

int deleteMin(minHeap* a, int x){
    int root = a->elem[0];
    a->count--;

    int last = a->elem[a->count];
    int ndx = 0;

    while (1) {
        int lc = 2*ndx + 1;
        int rc = lc + 1;
        int small = ndx;

        if (lc < a->count && a->elem[lc] < a->elem[small])
            small = lc;

        if (rc < a->count && a->elem[rc] < a->elem[small])
            small = rc;

        if (small == ndx) break;

        int temp = a->elem[ndx];
        a->elem[ndx] = a->elem[small];
        a->elem[small] = temp;

        ndx = small;
    }

    a->elem[ndx] = last;
    return root;
}
void heapSort(minHeap* A){
    insertAllMinHeap(A);
    display(*A);
    int oldCount = A->count;
    while(A->count != 0){
        int least = deleteMin(A, A->elem[A->count-1]);
        A->elem[A->count] = least;
    }
    A->count = oldCount;
    display(*A);
}

void display(minHeap a){
    int ndx = 0;
    while(ndx < a.count){
        printf("%d ", a.elem[ndx]);
        ndx++;
    }
    printf("\n");
}