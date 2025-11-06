#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}*Tree;

typedef struct{
    Tree arr[10];
    int top;
}Stack;

void freeNodes(Tree* root) {
    if (*root == NULL) return;

    freeNodes(&(*root)->left);
    freeNodes(&(*root)->right);

    free(*root);
    *root = NULL; 
}


void insert(Tree* head, int x){
    if(*head == NULL){
        *head = (Tree)malloc(sizeof(struct node));
        (*head)->data = x;
        (*head)->left = NULL;
        (*head)->right = NULL;
    }else if(x <= (*head)->data){
        insert(&(*head)->left, x);
    }else{
        insert(&(*head)->right, x);
    }
}

void push(Stack* yes, Tree child){
    if(yes->top < 10 - 1){
        yes->arr[++yes->top] = child;
    }
}

int top(Stack yes){
    return yes.arr[yes.top]->data;
}

Tree pop(Stack* yes){
    return yes->arr[yes->top--];
}

//my idea for iteratively traversing this through pre-order is store the right children in the stack
void preOrderTrav(Tree head){
    Stack rightChildren = {{NULL}, -1};
    Tree temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        if(temp->right != NULL){
            push(&rightChildren, temp->right);
        }

        temp = temp->left;
    }
    //after storing it go through the stack
    while(rightChildren.top != -1){
        temp = pop(&rightChildren);
        while(temp != NULL){
            printf("%d ", temp->data);
            if(temp->right != NULL){
                push(&rightChildren, temp->right);
            }

            temp = temp->left;
        }
    }

}


//recursively(no pun intended cause this is iterative) reach for the farthest left node and then process the right nodes
void inOrderTrav(Tree head){
    Stack children = {{NULL}, -1};
    Tree temp = head, trav;
    while(temp != NULL){
        push(&children, temp);
        temp = temp->left;
    }

    while(children.top != -1){
        temp = pop(&children);
        if(temp->right != NULL){
            push(&children, temp->right);
            trav = temp->right->left;
            while(trav != NULL){
                push(&children, trav);
                trav = trav->left;
            }
        }

        printf("%d ", temp->data);
    }

}


int main(){
    Tree root = NULL;
    insert(&root, 15);
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 8);
    insert(&root, 12);
    insert(&root, 17);
    insert(&root, 25);
    insert(&root, 11);

    // preOrderTrav(root);
    inOrderTrav(root);
    
    freeNodes(&root);
}