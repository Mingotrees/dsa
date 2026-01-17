#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdbool.h>
#define MAX 4

typedef struct{
    char elem[MAX];
    int beginning;
    int end;
}Queue;

void initialize(Queue* B);
void enqueue(Queue* B, char elem);
void dequeue(Queue* B);
char front(Queue B);
bool isEmpty(Queue B);
bool isFull(Queue B);
void printQueue(Queue* B);
void sortQueue(Queue* B);

int main(){
    Queue A;
    initialize(&A);
    enqueue(&A, 'u');
    enqueue(&A, 's');
    enqueue(&A, 'c');
    // enqueue(&A, 'c');
    printQueue(&A);
    sortQueue(&A);
    printQueue(&A);

    // for(int ndx = 0; ndx < 3; ndx++){
    //     dequeue(&A);
    //     printQueue(&A);
    // }
}

/*
* Front must be behind of rear by 1 counter clockwise
*/
void initialize(Queue* B){
    B->beginning = 0;
    B->end = 1;
}

void enqueue(Queue* B, char elem){
    if(!isFull(*B)){
        B->end = (B->end + MAX - 1) % MAX;
        B->elem[B->end] = elem;
    }else{
        printf("iz full\n");
    }
}

void dequeue(Queue* B){
    if(!isEmpty(*B)){
        B->beginning = (B->beginning + MAX - 1) % MAX;
    }else{
        printf("List Empty\n");
    }
}

char front(Queue B){
    return isEmpty(B) ? '\0' : B.elem[B.beginning];
}

bool isEmpty(Queue B){
    return ((B.end + MAX - 1) % MAX) == B.beginning ? true : false;
}

bool isFull(Queue B){
    return (B.end + MAX - 2) % MAX == B.beginning ? true: false;
}

void printQueue(Queue* B){
    if(!isEmpty(*B)){
        int ndx = (B->end + MAX - 1) % MAX;
        while(B->beginning != ndx){
            char temp = front(*B);
            printf("%c ", temp);
            dequeue(B);
            enqueue(B, temp);
        }
        printf("\n");
    }
}

void sortQueue(Queue* B){
    Queue temp;
    initialize(&temp);
    enqueue(&temp, front(*B));
    dequeue(B);

    while(!isEmpty(*B)){
        int stop = (temp.end + MAX - 1) % MAX;
        char elem = front(*B), hold;
        for(;temp.beginning != stop && front(temp) < elem; enqueue(&temp, hold)){
            hold = front(temp);
            dequeue(&temp);
        }
        enqueue(&temp, elem);

        for(;temp.beginning != stop; enqueue(&temp, hold)){
            hold = front(temp);
            dequeue(&temp);
        }

        dequeue(B);
    }
    
    while(!isEmpty(temp)){
        enqueue(B, front(temp));
        dequeue(&temp);
    }
}