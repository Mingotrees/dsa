#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 20

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    char marked;
}*Tree;

typedef struct{
    Tree arr[10];
    int top;
}Stack;

typedef struct{
    Tree arr[QUEUE_MAX];
    int front;
    int rear;
}Queue;

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
        (*head)->marked = 'f';
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

Tree top(Stack yes){
    Tree retVal = NULL;
    if(yes.top != -1){
        retVal = yes.arr[yes.top]; 
    }
    return retVal;
}

Tree pop(Stack* yes){
    Tree temp = yes->arr[yes->top--];
    return temp != NULL ? temp : NULL;
}

//my idea for iteratively traversing this through pre-order is store the right children in the stack
void preOrderTrav(Tree head){
    // Stack rightChildren = {{NULL}, -1};
    // Tree temp = head;
    // while(temp != NULL){
    //     printf("%d ", temp->data);
    //     if(temp->right != NULL){
    //         push(&rightChildren, temp->right);
    //     }

    //     temp = temp->left;
    // }
    // //after storing it go through the stack
    // while(rightChildren.top != -1){
    //     temp = pop(&rightChildren);
    //     while(temp != NULL){
    //         printf("%d ", temp->data);
    //         if(temp->right != NULL){
    //             push(&rightChildren, temp->right);
    //         }

    //         temp = temp->left;
    //     }
    // }

    //internet ver
    Stack children = {{NULL}, -1};
    Tree temp;
    push(&children, head);
    while(children.top != -1){
        temp = pop(&children);
        printf("%d ", temp->data);
        if(temp->right != NULL) push(&children, temp->right);
        if(temp->left != NULL) push(&children, temp->left);
    }

}


//recursively(no pun intended cause this is iterative) reach for the farthest left node and then process the right nodes
void inOrderTrav(Tree head){
    //ver 1
    // Stack children = {{NULL}, -1};
    // Tree temp = head, trav;
    // while(temp != NULL){
    //     push(&children, temp);
    //     temp = temp->left;
    // }

    // while(children.top != -1){
    //     temp = pop(&children);
    //     if(temp->right != NULL){
    //         push(&children, temp->right);
    //         trav = temp->right->left;
    //         while(trav != NULL){
    //             push(&children, trav);
    //             trav = trav->left;
    //         }
    //     }

    //     printf("%d ", temp->data);
    // }

    // internet ver
    Stack children = {{NULL}, -1};
    Tree temp = head;
    while(temp != NULL || children.top != -1){
        while(temp != NULL){
            push(&children , temp);
            temp = temp->left;
        }

        temp = pop(&children);
        printf("%d ", temp->data);
        temp = temp->right;
    }

}

//one stack method with extra member in struct
// void postOrderTrav(Tree head){
//     Stack children = {{NULL}, -1};
//     Tree temp = head, trav;
//     while(temp != NULL){
//         push(&children, temp);
//         temp = temp->left;
//     }

//     while(children.top != -1){
//         temp = top(children);
//         if(temp->right != NULL && temp->marked == 'f'){
//             temp->marked = 't';
//             push(&children, temp->right);
//             trav = temp->right->left;
//             while(trav != NULL){
//                 push(&children, trav);
//                 trav = trav->left;
//             }
//         }else{
//             temp = pop(&children);
//             printf("%d ", temp->data);
//         }

//     }

// }

//two stack method
void postOrderTrav(Tree head){
    //this shit never workes for trees that aren't binary search trees;
    // Stack children = {{NULL}, -1};
    // Stack rightChildren = {{NULL}, -1};
    // Tree temp = head, trav, xav = NULL;
    // while(temp != NULL){
    //     push(&children, temp);
    //     temp = temp->left;
    // }

    // while(children.top != -1){
    //     temp = pop(&children);
    //     if(temp->right != NULL){
    //         push(&rightChildren, temp);
    //         push(&children, temp->right);
    //         trav = temp->right->left;
    //         while(trav != NULL){
    //             push(&children, trav);
    //             trav = trav->left;
    //         }
    //     }else{
    //         printf("%d ", temp->data);
    //         trav = top(rightChildren);
    //         if(trav != NULL && trav->right == temp){
    //             while(rightChildren.top != -1 && trav->right->data == temp->data){
    //                 trav = pop(&rightChildren);
    //                 printf("%d ", trav->data);
    //                 temp = trav;
    //             }
    //         }
                        
    //     }

    // }
    //internet version  
    if (head == NULL) return;
    Stack s1 = {{NULL}, -1}, s2 = {{NULL}, -1};

    push(&s1, head);
    while (s1.top != -1) {
        Tree node = pop(&s1);
        push(&s2, node);
        if (node->left != NULL) push(&s1, node->left);
        if (node->right != NULL) push(&s1, node->right);
    }

    while (s2.top != -1) {
        printf("%d ", pop(&s2)->data);
    }
  
}


void enqueue(Queue* A, Tree element){
    if((A->rear + 2)% QUEUE_MAX != A->front){
        A->rear = (A->rear + 1) % QUEUE_MAX;
        A->arr[A->rear] = element;
    }
}

Tree dequeue(Queue* A){
    Tree retVal = NULL;
    if((A->rear + 1) % QUEUE_MAX != A->front){
        retVal = A->arr[A->front];
        A->front = (A->front + 1) % QUEUE_MAX;
    }
    return retVal;
}


void levelOrderTrav(Tree head){
    Queue anatoly = {{NULL}, 1, 0};
    enqueue(&anatoly, head);
    int level = 0;
    Tree trav;
    while((anatoly.rear + 1) % QUEUE_MAX != anatoly.front){
        printf("Level %d: ", level++);
        int stopper = (anatoly.rear + 1) % QUEUE_MAX;
        while(anatoly.front != stopper){
            trav = dequeue(&anatoly);
            printf("%d ", trav->data);

            if(trav->left != NULL){
                enqueue(&anatoly, trav->left);
            }

            if(trav->right != NULL){
                enqueue(&anatoly, trav->right);
            }
        }
        printf("\n");
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
    insert(&root, 26);
    insert(&root, 27);

    // preOrderTrav(root);
    // inOrderTrav(root);
    // postOrderTrav(root);
    levelOrderTrav(root);
    // printf("%d", 1<<1);
    int** arr = (int**)malloc(sizeof(int*)*10);
    
    int dab[2] = {0,1};
    arr[0] = dab;
    printf("%d", arr[0][0]);

    free(arr);
    freeNodes(&root);
}