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
    // int lever = 0;
    for(ptr = &C; A != NULL && B != NULL;){
        // for(bPtr = B; bPtr != NULL && lever != 1; bPtr = bPtr->next){
        //     if(A->data == B->data){
        //         *ptr = (SET)malloc(sizeof(struct node));
        //         (*ptr)->data = A->data;
        //         ptr = &(*ptr)->next;
        //         lever = 1;
        //     }
        // }
        if(A->data < B->data){
            A = A->next;
        }else{
            if(A->data == B->data){
                *ptr = (SET)malloc(sizeof(struct node));
                (*ptr)->data = A->data;
                ptr = &(*ptr)->next;
                A = A->next;
            }
            B = B->next;
        }
    }
    *ptr = NULL;
    return C;
}

SET DifferenceSorted(SET A, SET B){
    SET C = NULL;
    SET* cPtr;
    for(cPtr = &C; A != NULL && B != NULL;){
        // for(bPtr = B; bPtr != NULL && bPtr->data != A->data; bPtr = bPtr->next){}
        // if(bPtr == NULL){
        //     *cPtr = (SET)malloc(sizeof(struct node));
        //     if(*cPtr != NULL){
        //         (*cPtr)->data = A->data;
        //         cPtr = &(*cPtr)->next;
        //     }
        // }
        if(A->data < B->data){
            *cPtr = (SET)malloc(sizeof(struct node));
            if(*cPtr != NULL){
                (*cPtr)->data = A->data;
                cPtr = &(*cPtr)->next;
            }
            A = A->next;
        }else{
            if(A->data == B->data){
                A = A->next;
            }
            B = B->next;
        }
    }

    while(A != NULL){
        *cPtr = (SET)malloc(sizeof(struct node));
        if(*cPtr != NULL){
            (*cPtr)->data = A->data;
            cPtr = &(*cPtr)->next;
        }
    }

    *cPtr = NULL;
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



