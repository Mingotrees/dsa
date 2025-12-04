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
void heapify(Tree*, int);
void heapifyRecursive(Tree*, int );


int main(){
    Tree T;
    T.count = 0;

    int data[] = {20, 5, 15, 22, 9, 13, 27, 3, 8};
    int n = sizeof(data)/sizeof(data[0]);

    printf("Inserting elements:\n");
    for(int i = 0; i < n; i++){
        insert(&T, data[i]);
        display(T);
    }

    printf("\nPerforming heapify to build min-heap...\n");
    for(int i = (T.count - 2) / 2; i >= 0; i--) {
        heapify(&T, i);
    }
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

void insert(Tree* T, int x){
    if(T->count < MAX){
        T->arr[T->count++] = x;
    }
}

int deleteMin(Tree* T){
    int temp = T->arr[0];
    T->arr[0] = T->arr[--T->count];
    heapify(T, 0);
    return temp;
}

void heapsort(Tree* T){
    int lastParent = (T->count-2)/2;
    while(lastParent >= 0){
        heapifyRecursive(T, lastParent--);
    }

    int oldCount = T->count;
    int end = oldCount - 1;
    while(T->count != 0){
        int small = deleteMin(T);
        T->arr[end--] = small;
    }
    T->count = oldCount;
}

//minheap
void heapify(Tree* T, int subtree){
    int flag = 0;
    int lc = subtree*2 + 1;
    int rc = lc + 1;
    while(subtree < T->count && flag != 1){
        int small = subtree;
        if(lc < T->count && T->arr[lc] < T->arr[small]){
            small = lc;
        }

        if(rc < T->count && T->arr[rc] < T->arr[small]){
            small = rc;
        }

        if(small != subtree){
            int temp = T->arr[subtree];
            T->arr[subtree] = T->arr[small];
            T->arr[small] = temp;
            subtree = small;
            lc = small*2 +1;
            rc = lc+1;
        }else{
            flag = 1;
        }
    }
    
}


void heapifyRecursive(Tree* T, int subtree){
    int lc = subtree*2 + 1;
    int rc = lc + 1;
    int small = subtree;

    if(lc < T->count && T->arr[lc] < T->arr[small]){
        small = lc;
    }

    if(rc < T->count && T->arr[rc] < T->arr[small]){
        small = rc;
    }

    if(small != subtree){
        int temp = T->arr[subtree];
        T->arr[subtree] = T->arr[small];
        T->arr[small] = temp;
        heapifyRecursive(T, small);
    }
    
}