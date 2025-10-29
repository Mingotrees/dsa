#include <stdio.h>
#include <stdlib.h>
#define MAX 0x5

typedef struct node{
    int data;
    struct node* link;
}*List;

typedef List Dictionary[MAX];

void display(Dictionary A);
int hash(int x);
int insert(Dictionary A, int value);
int delete(Dictionary A, int value);
Dictionary* initialize();

int main(){
    Dictionary* A = initialize();
    
    // Fill all indices 0–4
    insert(*A, 0);   // hash = 0
    insert(*A, 1);   // hash = 1
    insert(*A, 2);   // hash = 2
    insert(*A, 3);   // hash = 3
    insert(*A, 4);   // hash = 4

    // Add collisions for chaining
    insert(*A, 5);   // hash = 0
    insert(*A, 6);   // hash = 1
    insert(*A, 7);   // hash = 2
    insert(*A, 8);   // hash = 3
    insert(*A, 9);   // hash = 4

    printf("Before deletion:\n");
    display(*A);

    // Delete one from each index
    delete(*A, 0);
    delete(*A, 1);
    delete(*A, 2);
    delete(*A, 3);
    delete(*A, 4);

    printf("\n\nAfter deletion:\n");
    display(*A);
}


void display(Dictionary A){
    for(int ndx = 0; ndx < MAX; ndx++){
        List temp;
        printf("[%d]: ", ndx);
        for(temp = A[ndx]; temp != NULL; temp = temp->link){
            printf("%d", temp->data);
            if(temp->link != NULL){
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

int hash(int x){
    return ((x % MAX) + MAX) % MAX;
}

int insert(Dictionary A, int value){
    int hashVal = hash(value);
    List temp = A[hashVal];
    A[hashVal] = (List)malloc(sizeof(struct node));
    A[hashVal]->data = value;
    A[hashVal]->link = temp;
    
}
int delete(Dictionary A, int value){
    int hashVal = hash(value);
    List* ptr;
    for(ptr = &A[hashVal]; *ptr != NULL && (*ptr)->data != value; ptr = &(*ptr)->link){}
    if(*ptr != NULL){
        List temp = *ptr;
        *ptr = temp->link;
        free(temp);
    }
}

Dictionary* initialize(){
    return calloc(1, sizeof(Dictionary));
}

