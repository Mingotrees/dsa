#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}*LIST;

typedef struct{
    int counter;
    LIST beginning;
    LIST end;
}Queue;

void initialize(Queue* B);
void enqueue(Queue* B, int elem);
void dequeue(Queue* B);
int front(Queue B);
bool isEmpty(Queue B);
bool isFull(Queue B);
void printQueue(Queue* B);
void sort(Queue*);

int main(){
    Queue A;
    initialize(&A);
    for(int ndx = 2; ndx < 5; ndx++){
        enqueue(&A, ndx);
    }
    printQueue(&A);

    for(int ndx = 0; ndx < 3; ndx++){
        dequeue(&A);
        printQueue(&A);
    }
}

void initialize(Queue* B){
    B->beginning = B->end = NULL;
}

/*
* This method adds an element at the end of
* the queue
* @param queue pass this by address
* @param element depending on your structure pass an element
* @return nothing cousinS
*/
void enqueue(Queue* B, int elem){
    LIST temp = (LIST)malloc(sizeof(struct node));
    temp->data = elem;
    temp->next = NULL;
    if(isEmpty(*B)){
        B->beginning = temp;
    }else{
        B->end->next = temp;
    }
    B->end = temp;
}

void dequeue(Queue* B){
    if(!isEmpty(*B)){
        LIST temp = B->beginning;
        B->beginning = temp->next;
        free(temp);
        if(B->beginning == NULL){
            B->end = NULL;
        }
    }
}

int front(Queue B){
    return isEmpty(B) != true ? B.beginning->data : -1;
}

bool isEmpty(Queue B){
    return B.beginning == NULL ? true : false;
}

bool isFull(Queue B){
    return false;
}

void enqueueSorted()

void printQueue(Queue* B){
    if(!isEmpty(*B)){
        // version 1
        // inefficient
        // int temp = B->beginning->data;
        // printf("%d\n", temp);
        // dequeue(B);
        // enqueue(B, temp);
        // for(;B->beginning->data != temp;){
        //     int hold = B->beginning->data;
        //     printf("%d\n", hold);
        //     dequeue(B);
        //     enqueue(B, hold);
        // }

        
        //version 2

        int temp = front(*B);
        // problem of this implementation is what if naay duplicate
        do{
            int hold = front(*B);
            printf("%d\n", hold);
            dequeue(B);
            enqueue(B, hold);
        }while(front(*B) != temp);

        printf("\n");

        //version 
        //try new version of enqueueing and dequeueing(?)
    }else{
        printf("Queue Empty");
    }
}