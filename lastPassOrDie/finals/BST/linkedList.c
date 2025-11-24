#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}*Tree;

void display(Tree root);
void insert(Tree* root, int x);
void insertRecur(Tree* root, int x);
void freeNodes(Tree* root);
void delete(Tree* root, int x);
void deleteRecur(Tree* root, int x);


int main(){
    Tree root = NULL;
    insertRecur(&root, 15);
    insertRecur(&root, 10);
    insertRecur(&root, 20);
    insertRecur(&root, 8);
    insertRecur(&root, 12);
    insertRecur(&root, 17);
    insertRecur(&root, 25);
    insertRecur(&root, 18);
    display(root);
    printf("\n");
    deleteRecur(&root, 15);
    display(root);  
}

void freeNodes(Tree* root) {
    if (*root == NULL) return;

    freeNodes(&(*root)->left);
    freeNodes(&(*root)->right);

    free(*root);
    *root = NULL; 
}

void display(Tree root){
    if(root != NULL){
        printf("%d ", root->data);
        display(root->left);
        display(root->right);
    }
}

void insert(Tree* root, int x){
    Tree* ptr = root;
    while(*ptr != NULL){
        ptr = (x <= (*ptr)->data) ? (&(*ptr)->left) : (&(*ptr)->right);
    }

    *ptr = (Tree)malloc(sizeof(struct node));
    (*ptr)->data = x;
    (*ptr)->left = NULL;
    (*ptr)->right = NULL;
}

void insertRecur(Tree* root, int x){
    if(*root == NULL){
        Tree temp = (Tree)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->data = x;
            temp->left = temp->right = NULL;
            *root = temp;
        }
    }else if(x <= (*root)->data){
        insertRecur(&(*root)->left, x);
    }else{
        insertRecur(&(*root)->right, x);
    }
}

void delete(Tree* root, int x){
    Tree* ptr;
    //find the element
    for(ptr = root; *ptr != NULL && (*ptr)->data != x;){
        ptr = (x <= (*ptr)->data) ? &(*ptr)->left : &(*ptr)->right; 
    }

    //if element is found check cases
    /*
    * CASE 1: node has no children, simply delete
    * CASE 2: node has 1 children, change link and delete node
    * CASE 3: node has 2 children, 
    *  SOLUTIONS 
    *   3.1: Find the minimum element in the right subtree of that node copy the value and delete the duplicate node.
    *   3.2: Find the maximum element in the left subtree of that node, copy the value and delete the duplicate node.
    *
    */
    if(*ptr != NULL){
        Tree temp = *ptr;
        //this solution is finding the maximum of the left subtree
        if(temp->right != NULL && temp->left != NULL){
            Tree *trav;
            for(trav = &(*ptr)->right; *trav != NULL && (*trav)->left != NULL; trav = &(*trav)->left){}
            temp->data = (*trav)->data; 
            temp = *trav;
            *trav = temp->right;
        }else{
            *ptr = temp->left == NULL ? temp->right : temp->left; 
        }

        free(temp);
    }
}


void deleteRecur(Tree* root, int x){
    // traverse
    if(*root == NULL){
        printf("not found");
        return;
    }

    if((*root)->data == x){
        //case 3
        Tree temp = *root;
        if((*root)->left != NULL && (*root)->right != NULL){
            Tree *trav;
            for(trav = &(*root)->right; *trav != NULL && (*trav)->left != NULL; trav = &(*trav)->left){}
            temp->data = (*trav)->data; 
            temp = *trav;
            *trav = temp->right;    
        }else{//case 1 and 2
            *root = (*root)->right == NULL ? (*root)->right : (*root)->left;
        }

    }else{
        if(x < (*root)->data) deleteRecur(&(*root)->left, x);
        if(x > (*root)->data) deleteRecur(&(*root)->right, x);
    }

}





