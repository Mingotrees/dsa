#include <stdio.h>
#include <stdlib.h>
#define MAX 0x5

typedef int Dictionary[MAX];
typedef enum {EMPTY = -9999999, DELETED = -888888888} DictStatus;

void display(Dictionary A);
int hash(int x);
int insert(Dictionary A, int value);
int delete(Dictionary A, int value);
Dictionary* initialize();

int main(){
    Dictionary* A = initialize();


    // Fill all slots except index 3
    // (we’ll leave A[3] = EMPTY intentionally)
    (*A)[0] = 10;
    (*A)[1] = 20;
    (*A)[2] = 30;
    (*A)[4] = 40;
    // A[3] = EMPTY  ← the only empty slot

    // Now try inserting a value that hashes to 4
    // This will cause probing: 4 → 0 → 1 → 2 → stops BEFORE 3
    insert(*A, 9);

    printf("\nFinal state:\n");
    display(*A);
    free(A);
    
}

void display(Dictionary A){
    int ndx;
    for(int ndx = 0; ndx < MAX; ndx++){
        printf("[%d] ", ndx);
        for(int idx = 0; idx < MAX; idx++){
            int hashVal = hash(A[idx]);
            if(hashVal == ndx){
                printf("%d", A[idx]);
                if(idx < MAX){
                    printf(" -> ");
                }
            }
        }
        printf("\n");
    }

    printf("\nNormal Mode\n");
    for(int ndx = 0; ndx < MAX; ndx++){
        printf("[%d]: [%d]\n", ndx, A[ndx]);
    }
}

int hash(int x){
    return ((x % MAX) + MAX) % MAX;
}

int insert(Dictionary A, int value){
    //can also count honestly
    int hashVal = hash(value);
    int ndx, deletedPos = -77777, stop = (hashVal - 1 + MAX) % MAX;
    for(ndx = hashVal; ndx != stop && A[ndx] != EMPTY; ndx = ( ndx +1 ) % MAX){
        if(deletedPos < 0 && A[ndx] == DELETED){
            deletedPos = ndx;
        }
    }

    if(A[ndx] == EMPTY){
        A[ndx] = value;
    }else if(deletedPos >= 0){
        A[deletedPos] = value;
    }else{
        printf("full\n");
    }

}

int delete(Dictionary A, int value){
    int hashVal = hash(value);
    int ndx, stop = ((hashVal - 1) + MAX) % MAX;
    for(ndx = hashVal; ndx != stop && A[ndx] != value; ndx = (ndx+1)%MAX){}
    if(A[ndx] == value){
        A[ndx] = DELETED; 
    }else{
        printf("not found");
    }
}

Dictionary* initialize(){
    Dictionary* A = (Dictionary*)malloc(sizeof(Dictionary));
    for(int ndx = 0; ndx < MAX; ndx++){
        (*A)[ndx] = EMPTY;
    }
    return A;
}