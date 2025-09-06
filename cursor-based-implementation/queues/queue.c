#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 3

typedef struct{
    char data;
    int link;
}List;

typedef struct{
   List nodes[MAX];
    int avail;
}VHeap;

typedef struct{
    int front;
    int rear;
}Queue;

void initVHeap(VHeap*);
void initQueue(Queue*);
int allocSpace(VHeap*);
void deallocSpace(VHeap*, int);
bool isFull(VHeap);
bool isEmpty(Queue);
void enqueue(Queue*, VHeap*, char);
void dequeue(Queue*, VHeap*);


int main(){

}

void initVHeap(VHeap *A){
    A->avail = MAX-1;
    for(int ndx = 0; ndx < MAX; ndx++){
        A->nodes[ndx].link = ndx-1;    
    }   

}

 void initVQueue(Queue *A){
    A->front = A->rear = -1;
}

int allocSpace(VHeap *A){
    int temp = A->avail;
    if(temp != -1){
        A->avail = A->nodes[temp].link;
    }

    return temp;
}

void deallocSpace(VHeap *A, int ndx){
    if(ndx != -1){
        A->nodes[ndx].link = A->avail;
        A->avail = ndx;    
    }
}

bool isFull(VHeap B){
    return B.avail == -1 ? true : false;
}

bool isEmpty(Queue B){
    return B.front === -1 ? true : false;
}

void enqueue(Queue *B, VHeap *A, char elem){
    int space = allocSpace(A);
    if(space != -1){
       A->nodes[space].data = elem;
       A->nodes[space].link = -1;
       if(isEmpty(*B)){
           B->front = space;     
       }else{
           A->nodes[B->rear].link = space;
       }
       B->rear = space;
    }
}

void dequeue(Queue *B, VHeap *A){
    if(!isEmpty(*B)){
        int temp = B->front;
        B->front = A->nodes[temp].link;
        deallocSpace(temp);
        if(B->front = -1){
            B->rear = -1;
        }
    }
}

