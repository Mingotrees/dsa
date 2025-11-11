#include <stdio.h>
#define MAX 10

typedef struct 
{
    int arr[MAX];
    int lastNdx;
}priQueue;

void insert(priQueue*, int x);
int deleteMin(priQueue*);
void heapSort(priQueue);
void display(priQueue);
void swap(int* a, int *b);
void heapifyRar(priQueue* A, int subRoot);
void heapifySubtree(priQueue *M, int subroot);

int main(){
    // priQueue A = {.lastNdx = -1};
    // for(int ndx = 0; ndx < MAX; ndx++){
    //     A.arr[ndx] = -1;
    // }

    // insert()
    // A.arr[++A.lastNdx] = 3; //0
    // A.arr[++A.lastNdx] = 5; //1
    // A.arr[++A.lastNdx] = 9; //2
    // A.arr[++A.lastNdx] = 8; //3
    // A.arr[++A.lastNdx] = 6; //4
    // A.arr[++A.lastNdx] = 9; //5
    // A.arr[++A.lastNdx] = 10; //6
    // A.arr[++A.lastNdx] = 10; //7
    // A.arr[++A.lastNdx] = 18; //8
    // A.arr[++A.lastNdx] = 9; //9

    // insert(&A, 3);
    // insert(&A, 5);
    // insert(&A, 9);
    // insert(&A, 8);
    // insert(&A, 6);
    // insert(&A, 9);
    // insert(&A, 10);
    // insert(&A, 10);
    // insert(&A, 18);
    // insert(&A, 9);

    // display(A);
    // deleteMin(&A);
    // display(A);
    priQueue B = {{7,6,5,4,3,2,1}, 6};

    for(int ndx = (B.lastNdx-1)/2; ndx >= 0; ndx--){
        heapifyRar(&B, ndx);
        // heapifySubtree(&B, ndx);
    }

    for(int ndx = 0; ndx <= B.lastNdx; ndx++){
        printf("%d", B.arr[ndx]);
    }
    
    // display(B);
    // insert(&A, 4);
}

void display(priQueue A){
    //brute force display
    // for(int ndx = 0; ndx <= A.lastNdx; ndx++){
    //     printf("%-5d ", A.arr[ndx]);
    // }

    // printf("\n");

    // for(int ndx = 0; ndx <= A.lastNdx; ndx++){
    //     printf("%-5d ", ndx);
    // }

    // printf("\n\n");
    int temp;
    printf("Indices:");
    temp = 0;
    while(temp <= A.lastNdx){   
        printf("%6d", temp);
        temp++;
    }

    printf("\nValues:");
    while((temp  = deleteMin(&A))!= -1){
        printf("%5d ", temp);
    }
    printf("\n\n");
}

void insert(priQueue* A, int x){
    //version 1, insert the elem first then shift
    // A->arr[++A->lastNdx] = x;
    // int temp = A->lastNdx;
    // int parentNdx = (A->lastNdx-1)/2;   
    // while(temp > 0 && A->arr[temp] < A->arr[parentNdx]){
    //     int store = A->arr[temp];
    //     A->arr[temp] = A->arr[parentNdx];
    //     A->arr[parentNdx] = store;
    //     temp = parentNdx;
    //     parentNdx = (parentNdx-1)/2;
    // }

    //version 2, pigeon hole method keep the hole open until position is final kudos to zeus elderfield
    if(A->lastNdx + 1 < MAX){
        int hole = ++A->lastNdx;
        int parent = (hole-1)/2;
        while(hole > 0 && A->arr[parent] > x){
            A->arr[hole] = A->arr[parent];
            hole = parent;
            parent = (parent-1)/2;
        }

        A->arr[hole] = x;
    }else{
        printf("Full la");
    }
}

int deleteMin(priQueue* A){
    // ver 1 switch first
    // int retVal = A->arr[0]; // store the curr root to be returned //get last leaf 
    // A->arr[0] = A->arr[A->lastNdx--]; //put last leaf in the position of the 1st root
    // int ndx = 0;
    // int flag = 0;
    // while(ndx < A->lastNdx && flag != 1){
    //     int lc = ndx * 2 + 2;
    //     int rc = lc + 1;
    //     int swap = A->arr[ndx];
    //     if(A->arr[lc] < A->arr[ndx] && A->arr[lc] < A->arr[rc] && A->arr[lc] != 0){
    //         A->arr[lc] = swap;
    //         A->arr[ndx] = A->arr[lc];
    //         ndx = lc;
    //     }else if(A->arr[rc] < A->arr[ndx] && A->arr[rc] != 0){
    //         A->arr[ndx] = A->arr[rc];
    //         A->arr[rc] = swap;
    //         ndx = rc;
    //     }else{
    //         flag = 1;
    //     }
    // }

    //ver 2 pigeon hole, kudos to zeus
    int retVal = -1;
    if(A->lastNdx >= 0){
        retVal = A->arr[0]; 
        int lastLeaf = A->arr[A->lastNdx--];

        int parent = 0;
        int lc = parent*2+1;
        int rc = lc+1;

        int child = A->arr[lc] > A->arr[rc] ? rc : lc;
        while(child <= A->lastNdx && A->arr[child] < lastLeaf){
            A->arr[parent] = A->arr[child];
            parent = child;
            lc = parent * 2 + 1;
            rc = lc + 1;
            child = A->arr[lc] > A->arr[rc] ? rc : lc;
        }

        A->arr[parent] = lastLeaf;
    }


    return retVal;
}

//no recursion
void heapifyRar(priQueue* A, int subRoot){
    /*
    * Step 1: Start with the non leaf node
    * Step 2: Check the right and left child check which one is smaller (minHeap)
    * Step 3: Swap the parent and that child
    * Step 4: Move on to the next non-leaf node and repeat steps 1-3
    * Optimized version by zeus elderifififeifem,fsemvlkafmkfvlma
    */
   //something is so wrong with this one bro :(
    int org = A->arr[subRoot];
    int lc = subRoot * 2 + 1;
    int rc = lc + 1;
    int child = A->arr[lc] < A->arr[rc] ? lc : rc;
    while(child <= A->lastNdx && A->arr[child] < org){
        A->arr[subRoot] = A->arr[child];
        subRoot = child;
        lc = subRoot*2 + 1;
        rc = lc + 1;
        child = (rc >= A->lastNdx || A->arr[lc]) < A->arr[rc] ? lc : rc; //this is amazing it checks first if any of the 1st cond is true  and check second if true

    }

    A->arr[subRoot] = org;  
}

void swap(int* a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//simon code

// void heapifySubtree(priQueue *M, int subroot) {
//     int smallest, left, right, done = 0;

//     while(!done) {
//         smallest = subroot;
//         left = subroot * 2 + 1;
//         right = left + 1;

//         if(right <= M->lastNdx && M->arr[left] < M->arr[smallest]) {
//             smallest = left;
//         }

//         if(right <= M->lastNdx && M->arr[right] < M->arr[smallest]) {
//             smallest = right;
//         }

//         if(smallest == subroot) {
//             done = 1;
//         } else {
//             int temp = M->arr[smallest];
    //             M->arr[smallest] = M->arr[subroot];
    //             M->arr[subroot] = temp;

    //             subroot = smallest;
    //         }
//     }
// }