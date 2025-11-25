#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{
    int data;
    struct node* next;
}*List;

typedef struct{
    List t[MAX];
    int root; 
}Tree;

Tree CREATE();
void MAKENULL(Tree* T);
int PARENT(int N, Tree T);
int LEFTMOST_CHILD(int N, Tree T);
int RIGHT_SIBLING(int N, Tree T);
int LABEL(int N, Tree T);
int ROOT(Tree T);
void PREORDER(int N, Tree T);
void INORDER(int N, Tree T);
void POSTORDER(int N, Tree T);

int main(){
    return 0;
}

void insertLast(){

}

Tree CREATE(){
    Tree temp = {{NULL}, 0};
    List* ptr = &(temp.t);
    return temp;
}

void MAKENULL(Tree* T){
    List temp = NULL;
    for(int ndx = 0; ndx < MAX; ndx++){   
        while(T->t[ndx] != NULL){
            temp = T->t[ndx];
            T->t[ndx] = temp->next;
            free(temp);
        }
    }
}

int PARENT(int N, Tree T){
    List temp = NULL;
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){   
        temp = T.t[ndx];
        while(temp != NULL && temp->data != N){}
        if(temp != NULL){
            break;
        }   
    }

    return temp == NULL ? -2 : ndx;
}

int LEFTMOST_CHILD(int N, Tree T){
    return T.t[N] != NULL ? T.t[N]->data : -2;
}

int RIGHT_SIBLING(int N, Tree T){
    List temp = NULL;
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){   
        temp = T.t[ndx];
        while(temp != NULL && temp->data != N){}
        if(temp != NULL){
            break;
        }
    }

    if(temp != NULL){
        temp->next;
    }

    return temp != NULL ? temp->data : -2;
}

int LABEL(int N, Tree T){
    return N;
}

int ROOT(Tree T){
    return T.root;
}

void PREORDER(int N, Tree T){
    int c;
    printf("%d ", N);
    c = leftmost_child(N, main);
    while(c != -2){
        preOrderDisplay(c, main);
        c = right_sibling(c, main);
    }
}

void INORDER(int N, Tree T){
    int c = LEFTMOST_CHILD(N, T); 
    if(c == -2){
        printf("%d, c");
    }else{
        INORDER(c, T);
        int child;
        for(child = RIGHT_SIBLING(c, T); child != -2 ; child = RIGHT_SIBLING(child, T)){
            INORDER(child, T);
        } 
    }
}


void POSTORDER(int N, Tree T){
    POSTORDERRECUR(N, T);
    printf("%d ", N);
}

void POSTORDERRECUR(int N, Tree T){
    int c;
    c = leftmost_child(N, T);
    while(c != -2){
        postOrderRecur(c, T);
        printf("%d ", label(c, T));
        c = right_sibling(c, T);
    }
}
