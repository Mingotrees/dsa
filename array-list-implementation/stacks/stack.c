/*
* This Program simulates the array implementation for stack
* using version 3 where struct stack will have a dynamically
* allocated array, top and MAX;
* It includes the basic operations as reflected in the 
* function prototypes
*
* Programmer: Jhanell R. Mingo 
* Created: 09/14/2025
* Last Updated: 09/14/2025 @ 10:26PM
*
*/
#include <stdio.h>
#include <stdlib.h>
#define INITIAL_SIZE 5


typedef struct{
    char *elemptr; 
    int top;
    int max;
}Stack;

typedef enum {
    FALSE, TRUE
}Boolean;


void initialize(Stack*, int);
void push(Stack*, char);
void pop(Stack*);
Boolean isEmpty(Stack);
Boolean isFull(Stack);
char peek(Stack);
void sort(Stack*);
void display(Stack);


int main(){
    Stack A;
    initialize(&A, INITIAL_SIZE);
    push(&A, '1');
    push(&A, '2');
    push(&A, '3');

    display(A);

    printf("\n\n");
    sort(&A);
    display(A);

    free(A.elemptr);
}

void display(Stack A){
    int ndx = A.top;
    for(;ndx < A.max; ndx++){
        printf("%c\n", A.elemptr[ndx]);
    }
}

void initialize(Stack* A, int size){
    A->max = size;
    A->elemptr = (char*)malloc(sizeof(char)*A->max);
    A->top = A->max;
}

Boolean isEmpty(Stack B){ 
    return B.top == B.max ? TRUE : FALSE;
}

Boolean isFull(Stack B){
    return B.top == 0 ? TRUE : FALSE;
}

void expandStack(Stack *B) {
    int oldMax = B->max;
    int newMax = oldMax * 2;
    int count = oldMax - B->top; // number of elements in stack

    char *newPtr = realloc(B->elemptr, sizeof(char) * newMax);
    if (newPtr == NULL) {
        printf("Realloc failed\n");
        return;
    }

    // shift existing elements to end of new array
    for (int i = 0; i < count; i++) {
        newPtr[newMax - 1 - i] = newPtr[oldMax - 1 - i];
    }

    B->elemptr = newPtr;
    B->top = newMax - count;
    B->max = newMax;
}


void push(Stack* A, char x){
    if(isFull(*A)){
        printf("Shit is Full\n");
        expandStack(A);
    }

    A->elemptr[--A->top] = x;
}

void pop(Stack* B){
    if(!isEmpty(*B)){
        B->top++;
    }
}

char peek(Stack B) {
    return (B.top < B.max) ? B.elemptr[B.top] : 0;
}

void sort(Stack* A) {
    Stack temp;
    initialize(&temp, A->max);

    // populate temp with first element
    push(&temp, peek(*A));
    pop(A);

    while (!isEmpty(*A)) {
        char carry = peek(*A);
        pop(A);

        while (!isEmpty(temp) && peek(temp) > carry) {
            push(A, peek(temp));
            pop(&temp);
        }
        push(&temp, carry);
    }

    while (!isEmpty(temp)) {
        push(A, peek(temp));
        pop(&temp);
    }

    free(temp.elemptr);
}