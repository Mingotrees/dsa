#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

void insert(SET A, int x);
void delete(SET A, int x);
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);
void initialize(SET A);
void displaySet(SET A);

int main(){
    SET D, E;
    initialize(E);
    insert(E, 1);
    insert(E, 0);
    insert(E, 9);
    initialize(D);
    insert(D, 2);
    insert(D, 3);
    insert(D, 1);

    printf("SET D:\n");
    displaySet(D);

    printf("SET E:\n");
    displaySet(E);

    printf("Union:\n");
    SET* C = Union(D, E);
    displaySet(*C);
    free(C);

    printf("Intersection:\n");
    C = Intersection(D, E);
    displaySet(*C);
    free(C);

    printf("Difference:\n");
    C = Difference(D, E);
    displaySet(*C);
    free(C);
}

void displaySet(SET A){
    printf("Current Elements in the Set: {");
    for(int ndx = 0; ndx < MAX; ndx++){
        printf(" %c", A[ndx] == 1 ? '1' : '0'); 
    }
    printf(" }\n");
    printf("THEIR INDEXES: ");
    for(int ndx = 0; ndx < MAX; ndx++){
        if(A[ndx] == 1){
            printf("%d ", ndx);
        } 
    }
    printf("\n");
}

void initialize(SET A){
    for(int ndx = 0; ndx < MAX; ndx++){
        A[ndx] = 0;
    }
}

void insert(SET A, int x){
    if(x < MAX){
        if(A[x] & 1 == 1){
            printf("Member Already Exists\n");
        }

        A[x] |= 1;
    }else{
        printf("Not a Valid Position\n");
    }
}

void delete(SET A, int x){
    if(x < MAX){
        if(A[x] == 0){
            printf("Member does not exist\n");
        }else{
            A[x] = 0;
            printf("Member deleted successfully\n");
        }
    }
}

SET* Union(SET A, SET B){
    SET* C = (SET*)malloc(sizeof(SET));
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] | B[ndx];
    }

    return C;
}

SET* Intersection(SET A, SET B){
    SET* C = (SET*)malloc(sizeof(SET));
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & B[ndx];
    }

    return C;
}

SET* Difference(SET A, SET B){ // A - B
    SET* C = (SET*)malloc(sizeof(SET));
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & !B[ndx];
    }

    return C;
}
