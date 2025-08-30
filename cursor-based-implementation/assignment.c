#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

/*
*
*   RUN IT LIKE THIS gcc assignment.c definitions.c -o assignment
*/

int main(){
    VirtualHeap B;
    initVirtualHeap(&B);
    List head;
    initList(&head);
    insertLast(&B, &head, 'u'); //0    //Linked List is in this order 3 -> 0 -> 1 -> 2 
    insertLast(&B, &head, 'c'); //1
    insertLast(&B, &head, 'k'); //2
    insertFirst(&B, &head, 'f'); //3
    traversal(B, head);
    deleteLast(&B, &head);
    deleteLast(&B, &head);
    deleteLast(&B, &head);
    deleteLast(&B, &head);
    traversal(B, head);
    // traversal(B, head);
    // checkAvailSpace(B);
    // sort(&B, &head);
    // insertSorted(&B, &head, 'j');
    // deleteElem(&B, &head, 'u');
    // traversal(B, head);
    // printf("\t(%d, %d)\n", head, B.avail);
    // checkAvailSpace(B);
    return 0;
}

