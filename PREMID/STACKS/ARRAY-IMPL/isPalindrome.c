#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 7
#define PALINDROME "racecar"


typedef struct{
    char elem[MAX];
    int top;
}Stack;

bool isPalindrome(Stack A, char word[]);
void push(Stack*, char);
void pop(Stack*);
bool isFull(Stack);
bool isEmpty(Stack);
void initialize(Stack*);
void display(Stack);


int main(){
    Stack A;
    initialize(&A);
    push(&A, 'r');
    push(&A, 'a');
    push(&A, 'c');
    push(&A, 'e');
    push(&A, 'c');
    push(&A, 'a');
    push(&A, 'r');
    display(A);
    if(isPalindrome(A, PALINDROME)){
        printf("Its a palindrome");
    }else{
        printf("nope");
    }

}

void push(Stack* A, char B){
    if(!isFull(*A)){
        A->elem[--A->top] = B;
    }else{
        printf("List is full\n");
    }
}

void pop(Stack* A){
    if(!isEmpty(*A)){
        A->top++;
    }else{
        printf("List is empty\n");
    }
}

bool isFull(Stack A){
    return A.top == 0 ? true : false; 
}

bool isEmpty(Stack A){
    return A.top == MAX ? true : false;
}

void initialize(Stack* A){
    A->top = MAX;
}

void display(Stack A){
    if(!isEmpty(A)){
        for(;A.top < MAX; A.top++){
            printf("%c\n", A.elem[A.top]);
        }
    }else{
        printf("List is Empty\n");
    }
    
}


bool isPalindrome(Stack A, char word[]){
    Stack temp;
    initialize(&temp);

    for(;A.top < MAX; A.top++){
        push(&temp, A.elem[A.top]);
    }

    return (strcmp(A.elem, word) == 0) ? true : false;
}