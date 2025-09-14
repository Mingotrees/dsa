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
    push(&A, 'z');
    push(&A, 'a');
    push(&A, 'b');
    push(&A, 'd');
    push(&A, 'u');
    push(&A, 'c');

    display(A);

    printf("\n\n");
    sort(&A);
    display(A);

    free(A.elemptr);
}

void display(Stack A){
    for(;!isEmpty(A); pop(&A)){
        printf("%c\n", peek(A));
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

void expandStack(Stack *B){
    //problem is you cannot exactly move the way you normally move becauase it was intialized in reverse
    Stack temp;
    initialize(&temp, B->max);
    for(;!isEmpty(*B); pop(B)){
        push(&temp, B->elemptr[B->top]);
    }

    char *newPtr = (char*)realloc(B->elemptr, sizeof(char)*(B->max*2));
    if(newPtr == NULL){
        printf("Malloc Failed");
        return;
    }

    B->elemptr = newPtr;
    B->max *= 2;
    B->top = B->max;

    for(;!isEmpty(temp); pop(&temp)){
        push(B, temp.elemptr[temp.top]);
    }

    free(temp.elemptr);
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

char peek(Stack B){
    return !isEmpty(B) ? B.elemptr[B.top] : 0;
}

void sort(Stack* A){
    Stack temp;
    initialize(&temp, A->max);

    //initially populate the temp stack so a comparison is better
    push(&temp, A->elemptr[A->top]);
    pop(A);

    while(!isEmpty(*A)){
        char carry = peek(*A);
        char tempTop = peek(temp);
        pop(A);
        while(!isEmpty(temp) && tempTop > carry){
            push(A, tempTop);
            pop(&temp);
        }
        push(&temp, carry);
    }

    while(!isEmpty(temp)){
        push(A, peek(temp));
        pop(&temp);        
    }

    free(temp.elemptr);
}

