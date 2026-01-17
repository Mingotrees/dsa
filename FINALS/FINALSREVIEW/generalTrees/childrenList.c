#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define ROOTNODE -1
#define DNE -2

typedef struct node{
    int data;
    struct node* next;
}*Cell;

typedef struct{
    Cell arr[MAX];
    int root;
}Tree;

typedef int Node;
typedef int ParentNdx;

Tree createTree();
Node right_sibling(Tree, Node);
Node leftmost_child(Tree, Node);
void insert(Tree*, Node, ParentNdx);
Node root(Tree);
Node parent(Tree, Node);
Node label(Node);
void preOrder(Tree, Node);
void inOrder(Tree, Node);
void postOrder(Tree, Node);

int main(){
    Tree yep = createTree();
    printf("\n-- PREORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 5 0 2 8 6 1 4 7 3\n");
    printf("Actual Output: ");
    preOrder(yep, root(yep));

    printf("\n\n-- INORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 0 5 8 2 4 1 7 6 3\n");
    printf("Actual Output: ");
    inOrder(yep, root(yep));

    printf("\n\n-- POSTORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 0 8 2 4 7 1 3 6 5\n");
    printf("Actual Output: ");
    postOrder(yep, root(yep));
    printf("%d", root(yep));
}

Tree createTree(){
    Tree new = {{0}, 5};
    /*
                   5
                /  |  \
                0   2   6 
                    /  /  \   
                   8  1    3   
                    /   \
                    4   7

    */
   insert(&new, 0, 5);
   insert(&new, 2, 5);
   insert(&new, 6, 5);
   insert(&new, 8, 2);
   insert(&new, 1, 6);
   insert(&new, 3, 6);
   insert(&new, 4, 1);
   insert(&new, 7, 1);
   return new;
}

void insert(Tree* T, Node x, ParentNdx y){
    Cell temp = (Cell)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = x;
        temp->next = NULL;
    }

    Cell* ptr;
    for(ptr = &T->arr[y]; *ptr != NULL; ptr = &(*ptr)->next){}
    *ptr = temp;
}

Node right_sibling(Tree  T, Node x){
    int ndx;
    Cell trav = NULL;
    for(ndx = 0; ndx < MAX && trav == NULL; ndx++){
        for(trav = T.arr[ndx]; trav != NULL && trav->data != x; trav = trav->next){}
    }

    return (trav != NULL && trav->next != NULL) ? trav->next->data : DNE;
}

Node leftmost_child(Tree T, Node x){
    return T.arr[x] != NULL ? T.arr[x]->data : DNE;
}

Node root(Tree T){
    return T.root;
}

Node parent(Tree T, Node x){
    int ndx;
    Cell trav = NULL;
    for(ndx = 0; ndx < MAX && trav == NULL; ndx++){
        for(trav = T.arr[ndx]; trav != NULL && trav->data != x; trav = trav->next){}
    }

    return trav != NULL ? ndx : DNE; 
}

Node label(Node n){
    return n;
}

void preOrder(Tree T, Node n){
    printf("%d ", n);
    Node c = leftmost_child(T, n);
    while(c != DNE){
        preOrder(T, c);
        c = right_sibling(T, c);
    }
}   

void inOrder(Tree T, Node n){
    Node c = leftmost_child(T, n);
    if(c == DNE){
        printf("%d ", n);
    }else{
        inOrder(T, c);
        printf("%d ", n);
        c = right_sibling(T, c);
        while(c != DNE){
            inOrder(T, c);
            c = right_sibling(T, c);
        }
    }
}

void postOrder(Tree T, Node n){
    Node c = leftmost_child(T, n);
    while(c != DNE){
        postOrder(T, c);
        printf("%d ", c);
        c = right_sibling(T, c);
    }
}
