#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef int* minHeap[SIZE];

void getInput(minHeap a, int* size){
    int inp, x ,y;
    printf("Enter the number of points: ");
    scanf("%d", size);
    for(int ndx = 0; ndx < *size; ndx++){
        a[ndx] = (int*)malloc(sizeof(int)*3);
        printf("Enter the x and y coordinate of point %d: ", ndx+1);
        scanf("%d %d", &a[ndx][0], &a[ndx][1]);
    }
}

void calculateDistanceFromOrigin(minHeap a, int count){
    for(int ndx = 0; ndx < count; ndx++){
        a[ndx][2] = (a[ndx][0] * a[ndx][0]) + (a[ndx][1] * a[ndx][1]); 
    }
}

void heapifySubTree(minHeap a, int root, int count){
    int smallest = root;
    int lc = root * 2 + 1;
    int rc = lc + 1;
    if(lc < count && a[lc][2] < a[smallest][2]){
        smallest = lc;
    }
    
    if(rc < count && a[rc][2] < a[smallest][2]){
        smallest = rc;
    }
    
    if(smallest != root){
        int* temp = a[smallest];
        a[smallest] = a[root];
        a[root] = temp;
        heapifySubTree(a, smallest, count);
    }
}



void heapify(minHeap a, int count){
    int lastNonLeaf = (count-1)/2;
    while(lastNonLeaf >= 0){
        heapifySubTree(a, lastNonLeaf--, count);
    }
}

int* deleteMin(minHeap a, int* count){
    int* root = a[0];
    a[0] = a[--(*count)];
    heapifySubTree(a, 0, *count);
   
    return root;
}

int main(){
    minHeap a;
    int numPoints, k, ndx;
    getInput(a, &numPoints);
    calculateDistanceFromOrigin(a, numPoints);
    heapify(a, numPoints);
    
    printf("Enter the value of K: ");
    scanf("%d", &k);
    minHeap closest; 
    printf("K closest points to origin: ");
    for(ndx = 0; ndx < k; ndx++){
        closest[ndx] = (int*)malloc(sizeof(int)*2);
        closest[ndx] = deleteMin(a, &numPoints);
        printf("(%d, %d) ", closest[ndx][0], closest[ndx][1]);
    }
    
    for(ndx = 0; ndx < k; ndx++){
        free(closest[ndx]); 
    }
    
    for (ndx = 0; ndx < numPoints; ndx++) {
        free(a[ndx]);
    }
    
    return 0;
}