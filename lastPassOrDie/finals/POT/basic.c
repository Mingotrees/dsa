#include <stdio.h>
#define MAX 10

typedef struct{
    int data[MAX];
    int count;
}PrioQueue;

//maxHeap 0th, ndx

void insert(PrioQueue* root, int x);
void subHeapify(PrioQueue* queue, int root);
void heapify(PrioQueue* queue);
void heapSort(PrioQueue* queue);
int deleteMax(PrioQueue* queue);
void display(PrioQueue queue);


int main(){
    PrioQueue origin = {{0}, 0};
    insert(&origin, 10);
    insert(&origin, 19);
    insert(&origin, 18);
    insert(&origin, 5);
    insert(&origin, 9);

    heapify(&origin);
    display(origin);
}


//There are two methods in inserting for priorityQueues to maintain POT property
// 1. InsertLast and bubble it if its parent is less than that element
// 2. Normal insert and then do heapify heapifying subTree starting from the last non-leaf element
// we can calculate the lastLeaf node using the formula lastParent = (count/2) - 1 this if the element is count
void insert(PrioQueue* root, int x){
 
    if(root->count < MAX){
        //1st way 
        //pigeon hole
        // int hole = root->count++;
        // int parent = hole / 2 - 1;
        // while(parent >= 0 && root->data[parent] < x){
        //     root->data[hole] = root->data[parent];
        //     hole = parent;
        //     parent = hole / 2 -1;
        // } 
        // root->data[hole] = x;
        //2nd way
        root->data[root->count++] = x;
    }
}


//two ways:
// 1. recursive
// 2. iterative
void subHeapify(PrioQueue* queue, int root){
    int big, flag = 0;
    int lc = root*2 + 1;
    int rc = lc + 1;
    while(root < queue->count && flag != 1){
        big = root;
        if(lc <= queue->count && queue->data[lc] > queue->data[big]){
            big = lc;
        }
        
        if(rc <= queue->count && queue->data[rc] > queue->data[big]){
            big = rc;
        }

        if(big != root){
            //swap
            int temp = queue->data[root];
            queue->data[root] = queue->data[big];
            queue->data[big] = temp;
            root = big; 
            lc = root*2 + 1;
            rc = lc + 1;
        }else{
            flag = 1;
        }
    }       
}

void heapify(PrioQueue* queue){
    int parent = queue->count/2 - 1;
    while(parent >= 0){
        subHeapify(queue, parent);
    }
}

void heapSort(PrioQueue* root){
    int oldLast = root->count;
    while(root->count != 0){
        int stephen = deleteMax(root);
        root->data[root->count] = stephen;
    }
    root->count = oldLast;
}

int deleteMax(PrioQueue* root){
    int retVal = root->data[0];
    root->data[0] = root->data[--(root->count)];
    subHeapify(root, 0);
    return retVal;
}

void display(PrioQueue queue){
    int level = 0;
    int ndx = 0; 
    while(ndx < queue.count){
        printf("%d ", queue.data[ndx]);
        ndx++;
    }
}



