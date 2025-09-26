/*
* Problem 1: "The Coffee Shop Order System"
*	Write a program that processes a series of operations: 'ORDER x' (customer orders item x) and 'SERVE' (barista serves the next order). 
*   For each SERVE operation, output the item being served. If there's no order to serve, output "NO_ORDER". Process all operations and show the final state. 
*   Operation “END” would stop the program and free the entire queue.
*
* Example input operations:
* ORDER 101
* ORDER 205
* SERVE
* ORDER 150
* SERVE
* SERVE
*
* Expected output:
* 101
* 205
* 150
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 20
#define CAPACITY 5
#define PROCESS 6

typedef struct{
    char item[MAX];
    int next;
}nodetype;

typedef struct{
    nodetype processes[MAX];
    int avail;
}VHeap;

typedef struct{
    VHeap* mem;
    int prelude;
    int epilogue;
}Queue;

void initQueue(Queue*);
void initVHeap(VHeap*);
int vmalloc(VHeap*);
void freespace(VHeap*, int);
void enqueue(Queue *q, char* x);
void dequeue(Queue *q);
bool isFull(Queue q);
bool isEmpty(Queue q);
char* top(Queue q);
void processOrder(Queue*, char* x);


int main(){
    char order[PROCESS][MAX];

    for(int ndx = 0; ndx < PROCESS; ndx++){
        printf("Input Process# %d: ", ndx);
        fgets(order[ndx], sizeof(char)*MAX, stdin);
        order[ndx][strcspn(order[ndx], "\n")] = '\0';
    }

    VHeap amazingMemory;
    initVHeap(&amazingMemory);
    Queue q1 = {.mem = &amazingMemory};
    initQueue(&q1);

    for(int ndx = 0; ndx < PROCESS; ndx++){
        processOrder(&q1, order[ndx]);
    }
    // char letter[50] = "I'm Wishing Now";
    // char* token = strtok(letter, " ");
    // while(token != NULL){
    //     printf("%s\n", token);
    //     token = strtok(NULL, " ");
    // }
}   


void initQueue(Queue* q){
    q->epilogue = q->prelude = -1;
}

void initVHeap(VHeap* h){
    h->avail = 0;
    for(int ndx = 1; ndx < CAPACITY; ndx++){
        h->processes[ndx-1].next = ndx; 
    }
    h->processes[CAPACITY - 1].next = -1;
}

int vmalloc(VHeap* h){
    int ndx = h->avail;
    if(ndx != -1){
        h->avail = h->processes[ndx].next;
    }
    return ndx;
}

void freespace(VHeap* h, int x){
    if(x != -1){
        h->processes[x].next = h->avail;
        h->avail = x;
    }
}

void processOrder(Queue* q, char* order){
    char* token = strtok(order, " ");
    if(token){
        if(strcmp(token, "ORDER") == 0){
            token = strtok(NULL, " ");
            enqueue(q, token);
        }else{
            if(isEmpty(*q)){
                printf("No Orders Yet to be Served");
            }else{
                printf("%s\n", top(*q));
                dequeue(q);
            }
        }
    }
}

void enqueue(Queue *q, char* x){
    if(!isFull(*q)){
        int ndx = vmalloc(q->mem);
        strcpy(q->mem->processes[ndx].item, x);
        q->mem->processes[ndx].next = -1;
        if(isEmpty(*q)){
            q->prelude = ndx;
        }else{
            q->mem->processes[q->epilogue].next = ndx;
        }
        q->epilogue = ndx;
    }
}

void dequeue(Queue *q){
    if(!isEmpty(*q)){
        int ndx = q->prelude;
        q->prelude = q->mem->processes[ndx].next;
        freespace(q->mem, ndx);
        if(isEmpty(*q)){
            q->epilogue = -1; 
        }
    }
}

bool isFull(Queue q){
    return q.mem->avail == -1 ? true : false;
}

bool isEmpty(Queue q){
    return q.prelude == -1 ? true : false;
}

char* top(Queue q){
    char* dummy = (char*)malloc(sizeof(char)*MAX);
    strcpy(dummy, "END");
    return q.prelude != -1 ? q.mem->processes[q.prelude].item : dummy; 
}