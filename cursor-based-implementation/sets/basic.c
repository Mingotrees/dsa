#include <stdio.h>
#define MAX 10

typedef struct{
    int data;
    int next;
}nodetype;

typedef struct{
    nodetype elems[MAX];
    int avail;
}VHeap;

typedef struct{
    VHeap* heap;
    int head;
}SET;

void insert();
void delete();
void display();
SET Union();
SET Intersection();
SET Difference();


int main(){

}