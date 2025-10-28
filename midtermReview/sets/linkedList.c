#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}*SET;

void display(SET A, char* str);
void insert(SET* A, int x);
void initialize(SET* A);
void delete(SET* A, int x);
bool isSubset(SET A, SET B);
SET init2();
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
bool isMember(SET A, int x);


void freeList(SET* head) {
    SET temp;
    while (*head != NULL) {
        temp = *head;          // store current node
        *head = (*head)->next; // move head to next
        free(temp);            // free old head
    }
}

int main(){
    SET A = init2(), B = init2();
    insert(&A, 5);
    insert(&A, 3);
    insert(&A, 9);
    insert(&A, 1);
    insert(&A, 7);

    insert(&B, 2);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 9);
    insert(&B, 10);

    display(A, "SET A");
    display(B, "SET B");
    // SET C = UNION(A, B);
    // display(C, "UNION OF SET A & B");
    // freeList(&C);
    // C = INTERSECTION(A, B);
    // display(C, "INTERSECTION OF SET A & B");
    // freeList(&C);
    // C = DIFFERENCE(A, B);
    // display(C, "DIFFERENCE OF SET A & B");

    // printf("B is %s", isSubset(A, B) ? "a subset of A" : "is not a subset of A");
    freeList(&A);
    freeList(&B);
    // freeList(&C);
}

void display(SET A, char* str){
    printf("%s:{", str);
    while(A != NULL){
        printf("%d", A->data);
        if(A->next != NULL){
            printf(", ");
        }
        A = A->next;
    }
    printf("}\n");
}

//cannot do insertFirst kay u still have to check if that element does not already exist
void insert(SET* A, int x){
    SET* ndx;
    for(ndx = A; *ndx != NULL && (*ndx)->data != x; ndx = &(*ndx)->next){}
    if(*ndx == NULL){
        *ndx = (SET)malloc(sizeof(struct node));
        (*ndx)->data = x;
        (*ndx)->next = NULL;        
    } 
}

void initialize(SET* A){
    *A = NULL;
}

void delete(SET* A, int x){
    SET* ndx;
    for(ndx = A; *ndx != NULL && (*ndx)->data != x; ndx = &(*ndx)->next){}
    if(*ndx != NULL){
        SET temp = *ndx;
        *ndx = temp->next;
        free(temp);
    }
}

bool isSubset(SET A, SET B){
    // is b a subest of a ?
    bool flag = true;
    for(;B != NULL && flag != false; B = B->next){
        SET ndx;
        for(ndx = A; ndx != NULL && ndx->data != B->data; ndx = ndx->next){}
        if(ndx == NULL){
            flag = false;
        }
    }

    return flag;
}

SET init2(){
    return NULL;
}

//unsorted
SET UNION(SET A, SET B){
    SET C = init2(), trav = A;
    SET* ndx = &C;
    //populate C with all elements of A first
    while(trav != NULL){
        *ndx = (SET)malloc(sizeof(struct node));
        if(*ndx != NULL){
            (*ndx)->data = trav->data;
            ndx = &(*ndx)->next;
        }
        trav = trav->next;
    }

    for(trav = B; trav != NULL; trav = trav->next){
        SET travis;
        for(travis = A; travis != NULL && travis->data != trav->data; travis = travis->next){}
        if(travis == NULL){
            *ndx = (SET)malloc(sizeof(struct node));
            if(*ndx != NULL){
                (*ndx)->data = trav->data;
                ndx = &(*ndx)->next;
            }   
        }
    }
    *ndx = NULL;
    return C;
}

SET INTERSECTION(SET A, SET B){
    SET C = init2();
    SET* ptr = &C;
    while(A != NULL){
        SET trav;
        for(trav = B; trav != NULL && trav->data != A->data; trav = trav->next){}
        if(trav != NULL){
            *ptr = (SET)malloc(sizeof(struct node));
            if(*ptr != NULL){
                (*ptr)->data = trav->data;
                ptr = &(*ptr)->next;
            }
        }
        A = A->next;
    }
    *ptr = NULL;
    return C;
}

SET DIFFERENCE(SET A, SET B){
    SET C = init2();
    SET* ptr = &C;
    while(A != NULL){
        SET trav;
        for(trav = B; trav != NULL && trav->data != A->data; trav = trav->next){}
        if(trav == NULL){
            *ptr = (SET)malloc(sizeof(struct node));
            if(*ptr != NULL){
                (*ptr)->data = A->data;
                ptr = &(*ptr)->next;
            }
        }
        A = A->next;
    }
    
    *ptr = NULL;
    return C;
}

bool isMember(SET A, int x){
    while(A != NULL && A->data != x){        
        A = A->next;
    } 
    return A != NULL ? true : false;
}