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
#define MAX 20

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



int main(){
    char letter[50] = "I'm Wishing Now";
    char* token = strtok(letter, " ");
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}   