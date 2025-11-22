#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef enum { ROOT = -1, NULLTREE = -2} TreeVal;

typedef int Tree[MAX];
typedef int Node;

//returns the value of the parent
Node parent(Node, Tree);

//returns the value of the leftmost child
Node leftmost_child(Node, Tree);

//return the value of the right sibling b which is left of a
Node right_sibling(Node, Tree);

//returns the value of node
Node label(Node, Tree);

//returns root breh
Node RootVal(Tree);

void postOrderRecur(Node n, Tree main);

//creates a tree disclaimer: this is already predetermined
//cant insert in general tree
Tree* create();

void preOrderDisplay(Node n, Tree main);
void postOrderDisplay(Node n, Tree main);

//apparently this doesnt exist for general tree
//because in order is supposed to only have two
//children per parent aka binary trees
// void inOrderDisplay(Node n, Tree main);

int main(){
    Tree* t = create();
    preOrderDisplay(RootVal(*t), *t);
    printf("\n");
    postOrderDisplay(RootVal(*t), *t);
    printf("\n");
    inOrderDisplay(RootVal(*t), *t);
    free(t);
}

//ndx is the value tree[ndx] is the label

//returns the value of the parent
Node parent(Node n, Tree main){
    return main[n];
}

//arranged in artifical ordering where all children is
//arranged in ascending order
//returns the leftmost child
Node leftmost_child(Node n, Tree main){
    int ndx;
    for(ndx = 0; ndx < MAX && main[ndx] != n; ndx++){}
    return ndx < MAX ? ndx : NULLTREE;
}

//return the value of the right sibling b which is left of a
Node right_sibling(Node n, Tree main){
    int ndx;
    //immediately to the right of n on god
    for(ndx = n+1; ndx < MAX && main[ndx] != main[n]; ndx++){}
    return ndx < MAX ? ndx : NULLTREE;
}

//returns the value of node
Node label(Node n, Tree main){
    return n;
}

//returns root breh
Node RootVal(Tree main){
    int ndx;
    for(ndx = 0; ndx < MAX && main[ndx] != ROOT; ndx++){}
    return ndx < MAX ? ndx : NULLTREE;
}

//creates a tree disclaimer: this is already predetermined
//cant insert in general tree
Tree* create(){
    /*
    *   THIS IS THE PREMADE TREE
    *        ndx    |  value
    *         0     |   5                
    *         1     |   6
    *         2     |   5
    *         3     |   6
    *         4     |   1
    *         5     |   -1
    *         6     |   5
    *         7     |   1
    *         8     |   2
    *         9     |   -2
     */
    Tree* main = (Tree*)malloc(sizeof(Tree));
    Tree val = {5, 6, 5, 6, 1, -1, 5, 1, 2, -2};
    for(int ndx = 0; ndx < MAX; ndx++){
        (*main)[ndx] = val[ndx];
    }

    return main;
}

void preOrderDisplay(Node n, Tree main){
    Node c;
    printf("%d ", label(n, main));
    c = leftmost_child(n, main);
    while(c != NULLTREE){
        preOrderDisplay(c, main);
        c = right_sibling(c, main);
    }
}

void postOrderDisplay(Node n, Tree main){
    postOrderRecur(n, main);
    printf("%d", n);
}

void postOrderRecur(Node n, Tree main){
    Node c;
    c = leftmost_child(n, main);
    while(c != NULLTREE){
        postOrderRecur(c, main);
        printf("%d ", label(c, main));
        c = right_sibling(c, main);
    }
}
