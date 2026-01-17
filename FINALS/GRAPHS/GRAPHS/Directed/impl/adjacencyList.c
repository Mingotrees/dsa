#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
#define NOPATH 999

typedef struct node{
    int data;
    struct node* next;
}*List;

//1st version/ no added adj array
typedef List matrix[5];


matrix* build();
int first(matrix m, int v);
int next(matrix m, int v, int i);
int vertex(matrix m, int v, int i);
void display(matrix m);

int main(){
    matrix* m = build();
    display(*m);
}

matrix* build(){
    List* nodePtr;
    matrix* ret = (matrix*)calloc(1, sizeof(matrix));

    int a[SIZE][SIZE] = {{0,1,0,1,1},{0,0,1,0,0},{1,0,0,0,1},{0,0,1,0,1},{0,1,0,0,0}};
    for(int ndx = 0; ndx < SIZE; ndx++){
        nodePtr = &((*ret)[ndx]);
        for(int idx = 0; idx < SIZE; idx++){
            if(a[ndx][idx] == 1){
                *nodePtr = (List)malloc(sizeof(struct node));
                (*nodePtr)->data = idx;
                nodePtr = &(*nodePtr)->next;
            }
        }
        *nodePtr = NULL;
    }

    return ret;
}

int first(matrix m, int v){
    return m[v] != NULL ? m[v]->data : NOPATH;
}

int next(matrix m, int v, int i){
    List temp;
    for(temp = m[v]; temp != NULL && temp->data != i; temp = temp->next){}
    return temp->next != NULL ? temp->next->data : NOPATH;
}

int vertex(matrix m, int v, int i){
    return i;
}

void display(matrix m){
    for(int ndx = 0; ndx < SIZE; ndx++){
        printf("Nodes adjacent to %d: ", ndx);
        int i = first(m, ndx);
        while (i != NOPATH) {
            int w = vertex(m, ndx, i);
            printf("%d ", w);
            i = next(m, ndx, i);
        }
        printf("\n");
    }
}