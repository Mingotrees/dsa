#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  SIZE 0xFF

typedef struct {
   int elem[SIZE];
   int count;
}maxHeap;


void maxSubHeapify(maxHeap* s, int root);
void maxHeapifyTree(maxHeap* s);
void swap(int* a, int *b);
void heapSort(maxHeap* a);
void populate(maxHeap* a);
void display(maxHeap a);

int main(){
    system("cls");
    maxHeap A;
    populate(&A);
    display(A);
    heapSort(&A);
}

//recursive
void maxSubHeapify(maxHeap* s, int root){
    int left = root*2+1, right = left + 1, largest = root;
    if(left < s->count && s->elem[largest] < s->elem[left]){
        largest = left;
    }

    if(right < s->count && s->elem[largest] < s->elem[right]){
        largest = right;
    }

    if(largest != root){
        swap(&s->elem[root], &s->elem[largest]);
        maxSubHeapify(s, largest);
    }
}

void maxHeapifyTree(maxHeap* s){
    int lastNonLeaf = (s->count-2)/2;
    while(lastNonLeaf >= 0){
        maxSubHeapify(s, lastNonLeaf--);
    }
}

void swap(int* a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapSort(maxHeap* a){
    maxHeapifyTree(a);
    printf("Heapified: ");
    display(*a);
    int ndx = a->count;
    while(a->count > 1){
        swap(&a->elem[0], &a->elem[a->count-1]);
        a->count--;
        maxSubHeapify(a, 0);
    }
    a->count = ndx;
    printf("Sorted: ");
    display(*a);
}

void populate(maxHeap* a) {
    srand(time(NULL)); 
    a->count = 0;
    for (int i = 0; i < 10; i++) {
        a->elem[a->count++] = rand() % 100; 
    }
}
void display(maxHeap a){
    for(int ndx = 0; ndx < a.count; ndx++){
        printf("%d ", a.elem[ndx]);
    }
    printf("\n");
}
