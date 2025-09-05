#include <stdio.h>
#include <stdbool.h>
#define MAX 3

typedef struct{
    char elem[MAX];
    int start;
    int end;
}Queue;

void initialize(Queue* B);
void enqueue(Queue* B, char elem);
void dequeue(Queue* B);
int front(Queue B);
bool isEmpty(Queue B);
bool isFull(Queue B);
void printQueue(Queue* B);

int main(){
    Queue A;
    initialize(&A);
    enqueue(&A, 'u');
    // for(int ndx = 2; ndx < 5; ndx++){
    //     enqueue(&A, ndx);
    // }
    printQueue(&A);

    // for(int ndx = 0; ndx < 3; ndx++){
    //     dequeue(&A);
    //     printQueue(&A);
    // }
}

/*
* Front must be ahead of rear by 1
*/
void initialize(Queue* B){
    B->start = 2;
    B->end = 1;
}

void enqueue(Queue* B, char elem){
    if(!isFull(*B)){
        B->end = (B->end + 1) % MAX;
        B->elem[B->end] = elem;
    }else{
        printf("iz full\n");
    }
}

void dequeue(Queue* B){
    if(isEmpty(*B)){
        B->start = (B->start + 1) % MAX;
    }else{
        printf("List Empty\n");
    }
}

int front(Queue B){
    return isEmpty(B) ? -1 : B.elem[B.start];
}

bool isEmpty(Queue B){
    return (B.end + 1) % MAX == B.start ? true : false;
}

bool isFull(Queue B){
    return (B.end + 2) % MAX == B.start ? true: false;
}

void printQueue(Queue* B){
    if(!isEmpty(*B)){
        char temp = front(*B);
        do{
            char store = front(*B);
            printf("%c ", store);
            dequeue(B);
            enqueue(B, store);
        }while(front(*B) != temp);
    }
}