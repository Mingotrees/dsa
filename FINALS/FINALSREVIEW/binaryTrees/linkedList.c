#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef struct node{
    int data;
    struct node* LC;
    struct node* RC;
}*BST;

typedef struct{
    BST data[MAX];
    int top;
}Stack;

void insert(BST*, int );
void push(Stack* s, BST);
BST pop(Stack* s);
void init_stack(Stack*);
void insertRecursive(BST*, int );
void delete(BST*, int );
void deleteRecursive(BST* , int );
void preOrder(BST);
void preOrderRecursive(BST);
void inOrder(BST);
void inOrderRecursive(BST);
void postOrder(BST);
void postOrderRecursive(BST);

int main(){
    BST root = NULL;

    insertRecursive(&root, 25);
    insertRecursive(&root, 15);
    insertRecursive(&root, 35);
    insertRecursive(&root, 10);
    insertRecursive(&root, 20);
    insertRecursive(&root, 30);
    insertRecursive(&root, 34);
    insertRecursive(&root, 40);

    // Expected BST:
    //          25
    //        /    \
    //      15      35
    //     /  \    /  \
    //   10   20 30   40
    //             \
    //              34
    printf("Inorder Recur: ");
    inOrderRecursive(root); // Should print: 10 15 20 25 30 34 35 40
    printf("\n");
    printf("Inorder: ");
    inOrder(root); // Should print: 10 15 20 25 30 34 35 40
    printf("\n");
    
    printf("Preorder Recur: ");
    preOrderRecursive(root); // Should print: 25 15 10 20 35 30 34 40
    printf("\n");
    printf("Preorder: ");
    preOrder(root); // Should print: 25 30 15 10 20 35 30 34 40
    printf("\n");
    
    
    printf("Preorder Recur: ");
    postOrderRecursive(root); // Should print: 10 20 15 34 30 40 35 25
    printf("\n");
    printf("Preorder: ");
    postOrder(root); // Should print: 10 20 15 34 30 40 35 25
    printf("\n");
}

void insert(BST* T, int x){
    BST* trav = T;
    while(*trav != NULL && (*trav)->data != x){
        BST temp = *trav;
        if(x < temp->data){
            trav = &temp->LC;
        }else{ 
            trav = &temp->RC;
        }
    }

    if(*trav == NULL){
        *trav = (BST)malloc(sizeof(struct node));
        if(*trav != NULL){
            (*trav)->data = x;
            (*trav)->LC = (*trav)->RC = NULL; 
        }
    }else{
        printf("%d Already exist...\n", x);
    }
}

void insertRecursive(BST* T, int x){
    if(*T == NULL){
        *T = (BST)malloc(sizeof(struct node));
        if(*T != NULL){
            (*T)->data = x;
            (*T)->LC = NULL; 
            (*T)->RC = NULL;
        }
    }else{
        if(x < (*T)->data)insertRecursive(&(*T)->LC, x);
        if(x > (*T)->data)insertRecursive(&(*T)->RC, x);
    }
}

void delete(BST* T, int x){
    BST* trav;
    for(trav = T; *trav != NULL && (*trav)->data != x; trav = (x < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC){}
    if(*trav != NULL){
        BST temp = *trav;
        //immediate sucessor
        if(temp->RC != NULL && temp->LC != NULL){
            for(trav = &temp->RC; *trav != NULL && (*trav)->LC != NULL; trav = &(*trav)->LC){}
            temp->data = (*trav)->data;
            temp = *trav;
            *trav = (*trav)->RC;
        }else{
            *trav = temp->RC != NULL ? temp->RC : temp->LC;
        }
        free(temp);
    }
}

void deleteRecursive(BST*T , int x){

}

void preOrder(BST T){
    Stack s = {{NULL}, -1};
    push(&s, T);
    while(s.top != -1){
        T = pop(&s);
        printf("%d ", T->data);
        if(T->RC != NULL) push(&s, T->RC);
        if(T->LC != NULL) push(&s, T->LC);
    }
}

void push(Stack* s, BST x){
    if(s->top < MAX - 1){
        s->data[++s->top] = x; 
    }
}

BST pop(Stack* s){
    return s->top != -1 ? s->data[s->top--] : NULL;
}

void preOrderRecursive(BST T){
    if(T != NULL){
        printf("%d ", T->data);
        preOrderRecursive(T->LC);
        preOrderRecursive(T->RC);
    }
}

void inOrder(BST T){
    Stack s = {{NULL}, -1};
    while(T != NULL || s.top != -1){
        while(T != NULL){
            push(&s, T);
            T = T->LC;
        }

        T = pop(&s);
        printf("%d ", T->data);
        T = T->RC;
    }
}

void inOrderRecursive(BST T){
    if(T != NULL){
        inOrderRecursive(T->LC);
        printf("%d ", T->data);
        inOrderRecursive(T->RC);
    }
}

void postOrder(BST T){
    Stack s1 = {{NULL}, -1};
    Stack s2 = {{NULL}, -1};
    push(&s1, T);
    while(s1.top != -1){
        T = pop(&s1);
        push(&s2, T); 
        if(T->LC != NULL) push(&s1, T->LC);
        if(T->RC != NULL) push(&s1, T->RC);
    }

    while(s2.top != -1){
        printf("%d ", pop(&s2)->data);
    }
}

void postOrderRecursive(BST T){
     if(T != NULL){
        postOrderRecursive(T->LC);
        postOrderRecursive(T->RC);
        printf("%d ", T->data);
    }
}

