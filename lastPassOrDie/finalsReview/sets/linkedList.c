#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* link;
}*Set;

void insert(Set*, int);
void delete(Set*, int);
bool is_member(Set, int);
Set Union(Set, Set);
Set Intersection(Set, Set);
Set Difference(Set, Set);
void init_set(Set*);
void display(Set, char[]);

int main(){
    Set A, B;
    init_set(&A); init_set(&B);
    for(int ndx = 0; ndx < 4; ndx++){
        insert(&A, ndx);
        insert(&B, ndx+2);
    }
    insert(&A, 7);
    display(A, "SET A");
    display(B, "SET B");
    Set C = Union(A, B);
    display(C, "UNION OF A & B");

    C = Intersection(A, B);
    display(C, "INTERSECTION OF A & B");

    C = Difference(A, B);
    display(C, "DIFFERENCE OF A & B");
}

void insert(Set* ptr, int x){
    Set* trav;
    for(trav = ptr; *trav != NULL && (*trav)->data != x; trav = &(*trav)->link){}
    if(*trav == NULL){
        Set temp = (Set)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->data = x;
            temp->link = NULL;
        }
        
        *trav = temp;
        // *trav = (Set)malloc(sizeof(struct node));
        // if(*trav != NULL){
        //     (*trav)->data = x;
        //     (*trav)->link = NULL;
        // }
    }
}

void delete(Set* ptr, int x){
    Set* trav;
    for(trav = ptr; *trav != NULL && (*trav)->data != x; trav = &(*trav)->link){}
    if(*trav != NULL){
        Set temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

bool is_member(Set ptr, int x){
     Set trav;
    for(trav = ptr; trav != NULL && trav->data != x; trav = trav->link){}
    return trav != NULL ? true : false;
}

Set Union(Set A, Set B){
    Set C; init_set(&C);
    Set trav;
    for(trav = A; trav != NULL; trav = trav->link){insert(&C, trav->data);}
    for(trav = B; trav != NULL; trav = trav->link){insert(&C, trav->data);}

    return C;
}

Set Intersection(Set A, Set B){
    Set C; init_set(&C);
    Set trav;
    for(trav = A; trav != NULL; trav = trav->link){
        Set idx;
        for(idx = B; idx != NULL && idx->data != trav->data; idx = idx->link){}
        if(idx != NULL){
            insert(&C, trav->data);
        }
    }

    return C;
}

Set Difference(Set A, Set B){
    Set C; init_set(&C);
    Set trav;
    for(trav = A; trav != NULL; trav = trav->link){
        Set idx;
        for(idx = B; idx != NULL && idx->data != trav->data; idx = idx->link){}
        if(idx == NULL){
            insert(&C, trav->data);
        }
    }
    return C;
}
void init_set(Set* ptr){
    *ptr = NULL;
}

void display(Set A, char message[]){
     printf("%s: ", message);

    for(Set ndx = A; ndx != NULL; ndx = ndx->link){
        printf("%d ", ndx->data);
    }
    printf("\n");
}