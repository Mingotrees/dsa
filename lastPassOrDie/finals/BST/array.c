#include <stdio.h>
#define MAX 6

//my attempt, in progress

typedef struct{
    int arr[MAX];
    int count;
}Tree;

typedef enum {EMPTY = -1} TreeStatus;

void display(Tree root);
void insert(Tree* root, int x);
void delete(Tree* root, int x);
void initialize(Tree* root);

int main(){
    Tree main;
    initialize(&main);
    insert(&main, 15);
    insert(&main, 13);
    insert(&main, 25);
    insert(&main, 11);
    insert(&main, 20);
    insert(&main, 14);
    insert(&main, 15);
    delete(&main, 11);
    display(main);

}

void display(Tree root){
    for(int ndx = 0; ndx < MAX; ndx++){
        printf("%d ", root.arr[ndx]);
    }   
}

void initialize(Tree* root){
    for(int ndx = 0; ndx < MAX; ndx++){
        root->arr[ndx] = EMPTY;
    }
    root->count = 0;
}

void insert(Tree* root, int x){
    int ndx = 0;
    int lc = ndx * 2 + 1;
    int rc = lc + 1;
    while(ndx < MAX && root->arr[ndx] != EMPTY){
        if(lc < MAX && x <= root->arr[ndx]){
            ndx = lc;
        }else if(rc < MAX){
            ndx = rc;
        }else{
            break;
        }
        lc = ndx * 2 + 1;
        rc = lc + 1;
    }
    
    if(ndx < MAX){
        root->count++;
        root->arr[ndx] = x;
    }
}

void delete(Tree* root, int x){
    //find element
    int ndx = 0;
    int lc = ndx * 2 + 1;
    int rc = lc + 1;
    while(ndx < MAX && root->arr[ndx] != x && root->arr[ndx] != EMPTY){
        if(lc < MAX && x <= root->arr[ndx]){
            ndx = lc;
        }else if(rc < MAX){
            ndx = rc;
        }else{
            break;
        }
        lc = ndx * 2 + 1;
        rc = lc + 1;
    }

    if(ndx < MAX){
           
    }
}
