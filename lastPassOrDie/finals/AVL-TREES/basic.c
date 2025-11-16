#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 20

typedef struct node{
    int data;
    int height;
    struct node* left;
    struct node* right;
}*Tree;

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

int height(Tree subTree){
    return subTree != NULL ? subTree->height : 0;
}


//values for a balance tree would be {-1, 0, 1}
                //where > 1 or < -1 means the tree is unbalanced
                //if tree is > 1 it means it is unbalanced to the left subtree
                //if <-1 unbalanced in the right subtree
int skew(Tree node){
    return height(node->left) - height(node->right);
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
            printf("(%d, %d, %d)", trav->data, trav->height, skew(trav));

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


int max(int a, int b){
    return a > b ? a : b;
}

Tree createNode(int data){
    Tree temp = (Tree)malloc(sizeof(struct node));
    temp->data = data;
    temp->right = NULL;
    temp->left = NULL;
    temp->height = 0;

    return temp;
}

void insert(Tree* root, int data){
    if(*root == NULL){
        *root = createNode(data);
    }else if((*root)->data > data){
        insert(&(*root)->left, data);
    }else{
        insert(&(*root)->right, data);
    }

    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));
    //need to handle each unbalanced case
    //if skew(root) > 1 or skew(root) < -1 the tree is unbalanced if this is positive it is left heavy, right = right heavy
    //case 1 : for positive rotate right for negative rotate left. (universal solution) (ang i rotate ani kay ang child mismo)
    //1.1 skew(root) = +2 and skew(leftChild) = +1 meaning it is left heavy(many elements to the left of leftChild)
    //1.2 skew(root) = -2 and skew(rightChild) = -1 meaning it is right heavy
    //1.3 skew(root) = +- 2 and skew(rightChild/leftChild) = 0 


    //case 3 (complicated case): (ang i rotate ani kay ang 1st child sa gi skew na child); so example for positive (*root)->left->right;
    //3.1 skew(root) = +2 and skew(leftChild) = -1 meaning right heavy (solution)
    //3.2 skew(root) = -2 and skew(rightChild) = +1 meaning left heavy
    int balanceFactor = skew(*root);
    if(balanceFactor > 1 || balanceFactor < -1){
        int childBalance = balanceFactor > 1 ? skew((*root)->left) : skew((*root)->right);
        //case left left heavy -> therefore, right rotate it once
        Tree temp = *root;
        Tree childNode;

        if(childBalance >= 0 && balanceFactor > 1){
            childNode = temp->left;
            temp->left = childNode->right;
            childNode->right = temp;
        }else if(childBalance <= 0 && balanceFactor < -1){ //left rotate
            childNode = temp->right;
            temp->right = childNode->left;               
            childNode->left = temp;
        }else{ //hard case
            //LR CASE ROOT IS LEFT HEAVY BUT CHILD IS RIGHT HEAVY
            //do left and then right rotate
            Tree extra;
            if(balanceFactor > 1 && childBalance < 0){
                extra = temp->left;
                childNode = temp->left->right;

                //left rotate
                extra->right = childNode->left;
                childNode->left = extra;

                //right rotate
                temp->left = childNode->right;
                childNode->right = temp;
            }else{
                extra = temp->right;
                childNode = temp->right->left;
                
                //right rotate
                extra->left = childNode->right;
                childNode->right = extra;
                
                //left rotate
                temp->right = childNode->left;
                childNode->left = temp;

            }
            extra->height = 1 + max(height(temp->left), height(temp->right));
        }
        

        *root = childNode;
        temp->height = 1 + max(height(temp->left), height(temp->right));
        childNode->height = 1 + max(height(childNode->left), height(childNode->right));
    }

}


int main(){
    Tree head = NULL;
    insert(&head, 15);
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 17);
    insert(&head, 30);
    insert(&head, 16);
    insert(&head, 18);

    levelOrderTrav(head);
    freeNodes(&head);
}