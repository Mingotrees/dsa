#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{
    int data;
    int left;
    int right;
}Node;

typedef struct{
    Node arr[MAX];
    int avail;
}VHeap;

typedef struct{
    int head;
    VHeap* space;    
}Tree;

void preOrder(Tree data, int root);
void postOrder(Tree data, int root);
void inOrder(Tree data, int root);
void insert(Tree* root, int x);
void insertRecur(Tree* root, int x);
int alloc(Tree* root);
void dealloc(Tree* root, int x);
void delete(Tree* root, int x);
void deleteRecur(Tree* root, int x);
void initHeap(Tree*);

int main(){
    Tree main;
    initHeap(&main);
    main.head = -1;
    insert(&main, 12);
    insert(&main, 24);
    insert(&main, 10);
    insert(&main, 16);
    insert(&main, 27);
    insert(&main, 13);
    insert(&main, 15);
    delete(&main, 12);
    preOrder(main, main.head);
    printf("\n");
    postOrder(main, main.head);
    printf("\n");
    inOrder(main, main.head);

}

void initHeap(Tree* a){
    a->space = (VHeap*)malloc(sizeof(VHeap));
    a->space->avail = MAX - 1;
    for(int ndx = 0; ndx < MAX; ndx++){
        a->space->arr[ndx].left = ndx -1;
        a->space->arr[ndx].right = -1;
        a->space->arr[ndx].data = 0;
    }
}

void insert(Tree* root, int x){
    int* trav;
    if(root->space->avail != -1){
        for(trav = &(root->head); *trav != -1 && root->space->arr[*trav].data != x;){
            if(x < root->space->arr[*trav].data){
                trav = &(root->space->arr[*trav].left);
            }else{
                trav = &(root->space->arr[*trav].right);
            }
        }
        
        int space = alloc(root);
        root->space->arr[space].data = x;
        root->space->arr[space].left = -1;
        root->space->arr[space].right = -1;
        *trav = space;
    }else{
        printf("no space or element is a duplicate\n");
    }
}

int alloc(Tree* root){
    int space = root->space->avail;
    if(space != -1){
        root->space->avail = root->space->arr[space].left;
    }

    return space;
}

void dealloc(Tree* root, int x){
    root->space->arr[x].left = root->space->avail;
    root->space->avail = x;
}

void delete(Tree* root, int x){
    int *trav;
    for(trav = &(root->head); *trav != -1 && root->space->arr[*trav].data != x;){
        if(x < root->space->arr[*trav].data){
            trav = &(root->space->arr[*trav].left);
        }else{
            trav = &(root->space->arr[*trav].right);
        }
    }

    if(*trav != -1){
        int temp = *trav;
        if(root->space->arr[temp].right != -1 && root->space->arr[temp].left != -1){
            int *trav2;
            //immediate sucessor
            for(trav2 = &(root->space->arr[temp].right); *trav != -1 && root->space->arr[*trav2].left != -1; trav2 = &(root->space->arr[*trav2].left)){}
            //switch data
            root->space->arr[temp].data = root->space->arr[*trav2].data;
            temp = *trav2;
            *trav2 =  root->space->arr[temp].right;
        }else{
            *trav = (root->space->arr[temp].left != -1) ? (root->space->arr[temp].left) : (root->space->arr[temp].right); 
        }
    }else{
        printf("elem not found");
    }
}


void preOrder(Tree data, int root){
    if(root != -1){
        printf("%d ", data.space->arr[root].data);
        preOrder(data, data.space->arr[root].left);
        preOrder(data, data.space->arr[root].right);
    }
}

void postOrder(Tree data, int root){
    if(root != -1){
        postOrder(data, data.space->arr[root].left);
        postOrder(data, data.space->arr[root].right);
        printf("%d ", data.space->arr[root].data);
    }
}

void inOrder(Tree data, int root){
    if(root != -1){
        inOrder(data, data.space->arr[root].left);
        printf("%d ", data.space->arr[root].data);
        inOrder(data, data.space->arr[root].right);
    }
}

void insertRecur(Tree* root, int x);
void deleteRecur(Tree* root, int x);