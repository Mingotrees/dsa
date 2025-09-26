#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}*SET;

void insert(SET* A, int x);
void delete(SET* B, int x);
SET UnionSorted(SET A, SET B);
SET IntersectionSorted(SET A, SET B);
SET DifferenceSorted(SET A, SET B);
void display(SET A);
void freeDemAll(SET* A);


int main(){
    SET A = NULL, B = NULL;
    for(int ndx = 0; ndx < 3; ndx++){
        insert(&A, 2-ndx);
        insert(&B, 4-ndx);
    }
    printf("SET A:\n");
    display(A);
    printf("SET B:\n");
    display(B);

    printf("Union:\n");
    SET C = UnionSorted(A, B);
    display(C);
    freeDemAll(&C);

    printf("Intersection:\n");
    C = IntersectionSorted(A, B);
    display(C);
    freeDemAll(&C);

    printf("Difference:\n");
    C = DifferenceSorted(A, B);
    display(C);
    freeDemAll(&C);

    freeDemAll(&A);
    freeDemAll(&B);
    freeDemAll(&C);
}

void insert(SET* A, int x){
    SET temp = *A;
    *A = (SET)malloc(sizeof(struct node));
    if(*A != NULL){
        (*A)->data = x;
        (*A)->next = temp;
    }
}

void delete(SET* B, int x){
    SET* ptr;
    for(ptr = B; *ptr != NULL && (*ptr)->data != x; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        SET temp = *ptr;
        *ptr = temp->next;
        free(temp);
    }
}

void freeDemAll(SET* A){
    for(;*A != NULL;){
        SET temp = *A;
        *A = temp->next;
        free(temp);
    }
}

//Data with the two sets are sorted
SET UnionSorted(SET A, SET B){
    SET C = NULL;
    SET* ptr;
    for(ptr = &C; A != NULL && B != NULL; ptr = &(*ptr)->next){
        *ptr = (SET)malloc(sizeof(struct node));
        if(A->data < B->data){
            (*ptr)->data = A->data;
            A = A->next;
        }else{
            if(A->data == B->data){
                A = A->next;
            }
            (*ptr)->data = B->data;
            B = B->next;
        }
    }

    if(A == NULL){
        A = B;
    }

    while(A != NULL){
        *ptr = (SET)malloc(sizeof(struct node));
        (*ptr)->data = A->data;
        A = A->next;
        ptr = &(*ptr)->next;
    }

    *ptr = NULL;
    return C;
    
}

SET IntersectionSorted(SET A, SET B){
    SET C = NULL, bPtr = NULL; 
    SET* ptr;
    int lever = 0;
    for(ptr = &C; A != NULL; A = A->next){
        for(bPtr = B; bPtr != NULL && lever != 1; bPtr = bPtr->next){
            if(A->data == B->data){
                *ptr = (SET)malloc(sizeof(struct node));
                (*ptr)->data = A->data;
                ptr = &(*ptr)->next;
                lever = 1;
            }
        }
    }
    *ptr = NULL;
    return C;
}

//inefficient as fuck
SET DifferenceSorted(SET A, SET B){
    SET C = NULL, bPtr;
    SET* cPtr = &C;
    while(A != NULL){ //populate c with all elements of A
        *cPtr = (SET)malloc(sizeof(struct node));
        (*cPtr)->data = A->data;
        A = A->next;
        cPtr = &(*cPtr)->next;
    }
    *cPtr = NULL;
    
    for(; B != NULL; B = B->next){ //delete elements of that are in B
        cPtr = &C;
        while(*cPtr != NULL && B->data != (*cPtr)->data){
            cPtr = &(*cPtr)->next;
        }
        if(*cPtr != NULL){
            SET temp = *cPtr;
            *cPtr = (*cPtr)->next;
            free(temp);
        }
    }

    return C;
}

void display(SET A){
    printf("Elements in The Set: {");
    while(A!=NULL){
        printf(" %d", A->data);
        A = A->next;
    }
    printf(" }\n");
}



