#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define ROOTNODE -1
#define DNE -2

typedef int Tree[MAX];
typedef int Node;

Tree* createTree();
Node right_sibling(Tree, Node);
Node leftmost_child(Tree, Node);
Node root(Tree);
Node parent(Tree, Node);
Node label(Node);
void preOrder(Tree, Node);
void inOrder(Tree, Node);
void postOrder(Tree, Node);

int main()
{
    Tree* yep = createTree();
    printf("\n-- PREORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 5 0 2 8 6 1 4 7 3\n");
    printf("Actual Output: ");
    preOrder(*yep, root(*yep));

    printf("\n\n-- INORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 0 5 8 2 4 1 7 6 3\n");
    printf("Actual Output: ");
    inOrder(*yep, root(*yep));

    printf("\n\n-- POSTORDER TRAVERSAL OF NODES --\n\n");
    printf("Expected Output: 0 8 2 4 7 1 3 6 5\n");
    printf("Actual Output: ");
    postOrder(*yep, root(*yep));
    printf("%d", root(*yep));
}

Tree* createTree(){
    /*
                   5
                /  |  \
                0   2   6 
                    /  /  \   
                   8  1    3   
                    /   \
                    4   7

*/
    Tree* ret = (Tree*)malloc(sizeof(Tree));
    (*ret)[0] = 5;
    (*ret)[1] = 6;
    (*ret)[2] = 5;
    (*ret)[3] = 6;
    (*ret)[4] = 1;
    (*ret)[5] = ROOTNODE;
    (*ret)[6] = 5;
    (*ret)[7] = 1;
    (*ret)[8] = 2;
    (*ret)[9] = DNE;

    return ret; 
}

Node right_sibling(Tree T, Node x){
    Node ndx;
    for(ndx = x + 1; ndx < MAX && T[ndx] != T[x]; ndx++){}
    return (ndx < MAX) ? ndx : DNE; 
}

Node leftmost_child(Tree T, Node x){
    Node ndx;
    for(ndx = 0; ndx < MAX && T[ndx] != x; ndx++){}
    return (ndx < MAX) ? ndx : DNE;
}

Node root(Tree T){
    Node ndx;
    for(ndx = 0; ndx < MAX && T[ndx] != ROOTNODE; ndx++){}
    return ndx;
}

Node parent(Tree T,  Node x){
    return T[x];
}

Node label(Node x){
    return x;
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
